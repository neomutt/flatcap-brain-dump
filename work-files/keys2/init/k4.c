#include "config.h"
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include "mutt/lib.h"
#include "address/lib.h"
#include "config/lib.h"
#include "email/lib.h"
#include "core/lib.h"
#include "alias/lib.h"
#include "conn/lib.h"
#include "gui/lib.h"
#include "mutt.h"
#include "attach/lib.h"
#include "browser/lib.h"
#include "color/lib.h"
#include "compmbox/lib.h"
#include "history/lib.h"
#include "imap/lib.h"
#include "index/lib.h"
#include "key/lib.h"
#include "menu/lib.h"
#include "ncrypt/lib.h"
#include "nntp/lib.h"
#include "notmuch/lib.h"
#include "parse/lib.h"
#include "pop/lib.h"
#include "postpone/lib.h"
#include "question/lib.h"
#include "send/lib.h"
#include "sidebar/lib.h"
#include "alternates.h"
#include "commands.h"
#include "external.h"
#include "globals.h"
#include "hook.h"
#include "mutt_logging.h"
#include "mutt_mailbox.h"
#include "muttlib.h"
#include "mx.h"
#include "nntp/adata.h" // IWYU pragma: keep
#include "protos.h"
#include "subjectrx.h"
#include "version.h"
#ifdef ENABLE_NLS
#include <libintl.h>
#endif
#ifdef USE_AUTOCRYPT
#include "autocrypt/lib.h"
#endif
#if defined(USE_DEBUG_NOTIFY) || defined(USE_DEBUG_BACKTRACE)
#include "debug/lib.h"
#endif
#ifndef DOMAIN
#include "conn/lib.h"
#endif
#ifdef USE_LUA
#include "mutt_lua.h"
#endif

const struct MenuOpSeq AliasDefaultBindings[] = { 0 };
const struct MenuOpSeq AttachmentDefaultBindings[] = { 0 };
#ifdef USE_AUTOCRYPT
const struct MenuOpSeq AutocryptDefaultBindings[] = { 0 };
#endif
const struct MenuOpSeq BrowserDefaultBindings[] = { 0 };
const struct MenuOpSeq ComposeDefaultBindings[] = { 0 };
const struct MenuOpSeq DialogDefaultBindings[] = { 0 };
const struct MenuOpSeq EditorDefaultBindings[] = { 0 };
const struct MenuOpSeq GenericDefaultBindings[] = { 0 };
const struct MenuOpSeq IndexDefaultBindings[] = { 0 };
const struct MenuOpSeq PagerDefaultBindings[] = { 0 };
const struct MenuOpSeq PgpDefaultBindings[] = { 0 };
const struct MenuOpSeq PostponedDefaultBindings[] = { 0 };
const struct MenuOpSeq QueryDefaultBindings[] = { 0 };
const struct MenuOpSeq SmimeDefaultBindings[] = { 0 };

const struct Mapping MenuNames[] = { 0 };
struct Mapping KeyNames[] = { 0 };

/// Array of key mappings, one for each #MenuType
struct KeymapList Keymaps[MENU_MAX];

/// Maximum length of a key binding sequence used for buffer in km_bindkey
#define MAX_SEQ 8

int endwin(void)
{
  return 0;
}

struct Keymap *alloc_keys(size_t len, keycode_t *keys)
{
  struct Keymap *p = MUTT_MEM_CALLOC(1, struct Keymap);
  p->len = len;
  p->keys = MUTT_MEM_CALLOC(len, keycode_t);
  memcpy(p->keys, keys, len * sizeof(keycode_t));
  return p;
}

struct Keymap *km_compare_keys(struct Keymap *k1, struct Keymap *k2, size_t *pos)
{
  *pos = 0;

  while (*pos < k1->len && *pos < k2->len)
  {
    if (k1->keys[*pos] < k2->keys[*pos])
      return k2;
    else if (k1->keys[*pos] > k2->keys[*pos])
      return k1;
    else
      *pos = *pos + 1;
  }

  return NULL;
}

void mutt_keymap_free(struct Keymap **ptr)
{
  if (!ptr || !*ptr)
    return;

  struct Keymap *km = *ptr;
  FREE(&km->macro);
  FREE(&km->desc);
  FREE(&km->keys);

  FREE(ptr);
}

void km_keyname(int c, struct Buffer *buf)
{
  const char *name = mutt_map_get_name(c, KeyNames);
  if (name)
  {
    buf_addstr(buf, name);
    return;
  }

  if ((c < 256) && (c > -128) && iscntrl((unsigned char) c))
  {
    if (c < 0)
      c += 256;

    if (c < 128)
    {
      buf_addch(buf, '^');
      buf_addch(buf, (c + '@') & 0x7f);
    }
    else
    {
      buf_add_printf(buf, "\\%d%d%d", c >> 6, (c >> 3) & 7, c & 7);
    }
  }
  else if ((c >= KEY_F0) && (c < KEY_F(256))) /* this maximum is just a guess */
  {
    buf_add_printf(buf, "<F%d>", c - KEY_F0);
  }
  else if ((c < 256) && (c >= -128) && IsPrint(c))
  {
    buf_add_printf(buf, "%c", (unsigned char) c);
  }
  else
  {
    buf_add_printf(buf, "<%ho>", (unsigned short) c);
  }
}

bool km_expand_key(struct Keymap *map, struct Buffer *buf)
{
  if (!map || !buf)
    return false;

  for (int i = 0; i < map->len; i++)
  {
    km_keyname(map->keys[i], buf);
  }

  return true;
}

int parse_keycode(const char *s)
{
  char *end_char = NULL;
  long int result = strtol(s + 1, &end_char, 8);
  /* allow trailing whitespace, eg.  < 1001 > */
  while (isspace(*end_char))
    end_char++;
  /* negative keycodes don't make sense, also detect overflow */
  if ((*end_char != '>') || (result < 0) || (result == LONG_MAX))
  {
    return -1;
  }

  return result;
}

int parse_fkey(char *s)
{
  char *t = NULL;
  int n = 0;

  if ((s[0] != '<') || (tolower(s[1]) != 'f'))
    return -1;

  for (t = s + 2; *t && isdigit((unsigned char) *t); t++)
  {
    n *= 10;
    n += *t - '0';
  }

  if (*t != '>')
    return -1;
  return n;
}

size_t parsekeys(const char *str, keycode_t *d, size_t max)
{
  int n;
  size_t len = max;
  char buf[128] = { 0 };
  char c;
  char *t = NULL;

  mutt_str_copy(buf, str, sizeof(buf));
  char *s = buf;

  while (*s && len)
  {
    *d = '\0';
    if ((*s == '<') && (t = strchr(s, '>')))
    {
      t++;
      c = *t;
      *t = '\0';

      n = mutt_map_get_value(s, KeyNames);
      if (n != -1)
      {
        s = t;
        *d = n;
      }
      else if ((n = parse_fkey(s)) > 0)
      {
        s = t;
        *d = KEY_F(n);
      }
      else if ((n = parse_keycode(s)) > 0)
      {
        s = t;
        *d = n;
      }

      *t = c;
    }

    if (!*d)
    {
      *d = (unsigned char) *s;
      s++;
    }
    d++;
    len--;
  }

  return max - len;
}

enum CommandResult km_bind_err(const char *s, enum MenuType mtype, int op, char *macro, char *desc, struct Buffer *err)
{
  enum CommandResult rc = MUTT_CMD_SUCCESS;
  struct Keymap *last = NULL, *np = NULL, *compare = NULL;
  keycode_t buf[MAX_SEQ];
  size_t pos = 0, lastpos = 0;

  size_t len = parsekeys(s, buf, MAX_SEQ);

  struct Keymap *map = alloc_keys(len, buf);
  map->op = op;
  map->macro = mutt_str_dup(macro);
  map->desc = mutt_str_dup(desc);

  /* find position to place new keymap */
  STAILQ_FOREACH(np, &Keymaps[mtype], entries)
  {
    compare = km_compare_keys(map, np, &pos);

    if (compare == map) /* map's keycode is bigger */
    {
      last = np;
      lastpos = pos;
      if (pos > np->eq)
        pos = np->eq;
    }
    else if (compare == np) /* np's keycode is bigger, found insert location */
    {
      map->eq = pos;
      break;
    }
    else /* equal keycodes */
    {
      /* Don't warn on overwriting a 'noop' binding */
      if ((np->len != len) && (np->op != OP_NULL))
      {
        static const char *guide_link = "https://neomutt.org/guide/configuration.html#bind-warnings";
        /* Overwrite with the different lengths, warn */
        struct Buffer *old_binding = buf_pool_get();
        struct Buffer *new_binding = buf_pool_get();

        km_expand_key(map, old_binding);
        km_expand_key(np, new_binding);

        char *err_msg = _("Binding '%s' will alias '%s'  Before, try: 'bind %s %s noop'");
        if (err)
        {
          /* err was passed, put the string there */
          buf_printf(err, err_msg, buf_string(old_binding), buf_string(new_binding),
                     mutt_map_get_name(mtype, MenuNames), buf_string(new_binding));
          buf_add_printf(err, "  %s", guide_link);
        }
        else
        {
          struct Buffer *tmp = buf_pool_get();
          buf_printf(tmp, err_msg, buf_string(old_binding), buf_string(new_binding),
                     mutt_map_get_name(mtype, MenuNames), buf_string(new_binding));
          buf_add_printf(tmp, "  %s", guide_link);
          mutt_error("%s", buf_string(tmp));
          buf_pool_release(&tmp);
        }
        rc = MUTT_CMD_WARNING;

        buf_pool_release(&old_binding);
        buf_pool_release(&new_binding);
      }

      map->eq = np->eq;
      STAILQ_REMOVE(&Keymaps[mtype], np, Keymap, entries);
      mutt_keymap_free(&np);
      break;
    }
  }

  if (map->op == OP_NULL)
  {
    mutt_keymap_free(&map);
  }
  else
  {
    if (last) /* if queue has at least one entry */
    {
      if (STAILQ_NEXT(last, entries))
        STAILQ_INSERT_AFTER(&Keymaps[mtype], last, map, entries);
      else /* last entry in the queue */
        STAILQ_INSERT_TAIL(&Keymaps[mtype], map, entries);
      last->eq = lastpos;
    }
    else /* queue is empty, so insert from head */
    {
      STAILQ_INSERT_HEAD(&Keymaps[mtype], map, entries);
    }
  }

  return rc;
}

enum CommandResult km_bindkey_err(const char *s, enum MenuType mtype, int op, struct Buffer *err)
{
  return km_bind_err(s, mtype, op, NULL, NULL, err);
}

enum CommandResult km_bindkey(const char *s, enum MenuType mtype, int op)
{
  return km_bindkey_err(s, mtype, op, NULL);
}

void create_bindings(const struct MenuOpSeq *map, enum MenuType mtype)
{
  STAILQ_INIT(&Keymaps[mtype]);

  for (int i = 0; map[i].op != OP_NULL; i++)
    if (map[i].seq)
      km_bindkey(map[i].seq, mtype, map[i].op);
}

void km_init(void)
{
  memset(Keymaps, 0, sizeof(struct KeymapList) * MENU_MAX);

  create_bindings(AliasDefaultBindings, MENU_ALIAS);
  create_bindings(AttachmentDefaultBindings, MENU_ATTACHMENT);
#ifdef USE_AUTOCRYPT
  create_bindings(AutocryptDefaultBindings, MENU_AUTOCRYPT);
#endif
  create_bindings(BrowserDefaultBindings, MENU_FOLDER);
  create_bindings(ComposeDefaultBindings, MENU_COMPOSE);
  create_bindings(DialogDefaultBindings, MENU_DIALOG);
  create_bindings(EditorDefaultBindings, MENU_EDITOR);
  create_bindings(GenericDefaultBindings, MENU_GENERIC);
  create_bindings(IndexDefaultBindings, MENU_INDEX);
  create_bindings(PagerDefaultBindings, MENU_PAGER);
  create_bindings(PgpDefaultBindings, MENU_PGP);
  create_bindings(PostponedDefaultBindings, MENU_POSTPONED);
  create_bindings(QueryDefaultBindings, MENU_QUERY);
  create_bindings(SmimeDefaultBindings, MENU_SMIME);
}

int main(int argc, char *argv[])
{
  return 0;
}
