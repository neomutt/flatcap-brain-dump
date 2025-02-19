// gcc -I. -o array array.c libcore.a libconfig.a libemail.a libaddress.a libmutt.a -lpcre2-8 -fsanitize=address -fno-sanitize-recover=address -lidn2

#include "config.h"
#include <dirent.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "mutt/lib.h"
#include "email/lib.h"
#include "maildir/lib.h"
#include "maildir/mdata.h"
#include "maildir/mdemail.h"
#include "maildir/private.h"
#include "progress.h"

#undef USE_HCACHE

bool C_FlagSafe;
bool C_Autocrypt;
SIG_ATOMIC_VOLATILE_T SigInt;

static void nm_edata_free(void **ptr)
{
  if (ptr)
  {
  }
}

void mx_alloc_memory(struct Mailbox *m)
{
  size_t s = MAX(sizeof(struct Email *), sizeof(int));

  if ((m->email_max + 25) * s < m->email_max * s)
  {
    mutt_error(_("Out of memory"));
    mutt_exit(1);
  }

  m->email_max += 25;
  if (m->emails)
  {
    mutt_mem_realloc(&m->emails, sizeof(struct Email *) * m->email_max);
    mutt_mem_realloc(&m->v2r, sizeof(int) * m->email_max);
  }
  else
  {
    m->emails = mutt_mem_calloc(m->email_max, sizeof(struct Email *));
    m->v2r = mutt_mem_calloc(m->email_max, sizeof(int));
  }
  for (int i = m->email_max - 25; i < m->email_max; i++)
  {
    m->emails[i] = NULL;
    m->v2r[i] = -1;
  }
}

static int mutt_autocrypt_process_autocrypt_header(struct Email *e, struct Envelope *env)
{
  if (e || env)
  {
  }
  return 0;
}

void mutt_progress_init(struct Progress *progress, const char *msg, enum ProgressType type, size_t size)
{
  if (progress || msg || type || size)
  {
  }
}

void mutt_progress_update(struct Progress *progress, size_t pos, int percent)
{
  if (progress || pos || percent)
  {
  }
}

mode_t mh_umask(struct Mailbox *m)
{
  if (m)
  {
  }
  return 0;
}

static void maildir_update_mtime(struct Mailbox *m)
{
  char buf[PATH_MAX];
  struct stat st;
  struct MaildirMboxData *mdata = maildir_mdata_get(m);

  snprintf(buf, sizeof(buf), "%s/%s", mailbox_path(m), "cur");
  if (stat(buf, &st) == 0)
    mutt_file_get_stat_timespec(&mdata->mtime_cur, &st, MUTT_STAT_MTIME);
  snprintf(buf, sizeof(buf), "%s/%s", mailbox_path(m), "new");

  if (stat(buf, &st) == 0)
    mutt_file_get_stat_timespec(&m->mtime, &st, MUTT_STAT_MTIME);
}

void maildir_entry_free(struct MdEmail **ptr)
{
  if (!ptr || !*ptr)
    return;

  struct MdEmail *md = *ptr;
  FREE(&md->canon_fname);
  email_free(&md->email);

  FREE(ptr);
}

struct MdEmail *maildir_entry_new(void)
{
  return mutt_mem_calloc(1, sizeof(struct MdEmail));
}

void maildirarray_clear(struct MdEmailArray *mda)
{
  if (!mda)
    return;

  struct MdEmail **mdp = NULL;
  ARRAY_FOREACH(mdp, mda)
  {
    maildir_entry_free(mdp);
  }

  ARRAY_FREE(mda);
}

void maildir_mdata_free(void **ptr)
{
  if (!ptr || !*ptr)
    return;

  // struct MaildirMboxData *mdata = *ptr;
  FREE(ptr);
}

struct MaildirMboxData *maildir_mdata_get(struct Mailbox *m)
{
  if (!m || ((m->type != MUTT_MAILDIR) && (m->type != MUTT_MH)))
    return NULL;
  return m->mdata;
}

struct MaildirMboxData *maildir_mdata_new(void)
{
  struct MaildirMboxData *mdata = mutt_mem_calloc(1, sizeof(struct MaildirMboxData));
  return mdata;
}

void maildir_edata_free(void **ptr)
{
  if (!ptr || !*ptr)
    return;

  struct MaildirEmailData *edata = *ptr;
  FREE(&edata->maildir_flags);

  FREE(ptr);
}

struct MaildirEmailData *maildir_edata_get(struct Email *e)
{
  if (!e)
    return NULL;
  return e->edata;
}

struct MaildirEmailData *maildir_edata_new(void)
{
  return mutt_mem_calloc(1, sizeof(struct MaildirEmailData));
}

void maildir_parse_flags(struct Email *e, const char *path)
{
  char *q = NULL;

  e->flagged = false;
  e->read = false;
  e->replied = false;

  struct MaildirEmailData *edata = maildir_edata_get(e);
  char *p = strrchr(path, ':');
  if (p && mutt_str_startswith(p + 1, "2,"))
  {
    p += 3;

    mutt_str_replace(&edata->maildir_flags, p);
    q = edata->maildir_flags;

    while (*p)
    {
      switch (*p)
      {
        case 'F':
          e->flagged = true;
          break;

        case 'R': /* replied */
          e->replied = true;
          break;

        case 'S': /* seen */
          e->read = true;
          break;

        case 'T': /* trashed */
          if (!e->flagged || !C_FlagSafe)
          {
            e->trash = true;
            e->deleted = true;
          }
          break;

        default:
          *q++ = *p;
          break;
      }
      p++;
    }
  }

  if (q == edata->maildir_flags)
    FREE(&edata->maildir_flags);
  else if (q)
    *q = '\0';
}

struct Email *maildir_parse_stream(enum MailboxType type, FILE *fp, const char *fname, bool is_old, struct Email *e)
{
  if (!e)
    e = email_new();
  e->env = mutt_rfc822_read_header(fp, e, false, false);

  struct stat st;
  fstat(fileno(fp), &st);

  if (!e->received)
    e->received = e->date_sent;

  /* always update the length since we have fresh information available. */
  e->body->length = st.st_size - e->body->offset;

  e->index = -1;

  if (type == MUTT_MAILDIR)
  {
    /* maildir stores its flags in the filename, so ignore the
     * flags in the header of the message */

    e->old = is_old;
    maildir_parse_flags(e, fname);
  }
  return e;
}

struct Email *maildir_parse_message(enum MailboxType type, const char *fname, bool is_old, struct Email *e)
{
  FILE *fp = fopen(fname, "r");
  if (!fp)
    return NULL;

  e = maildir_parse_stream(type, fp, fname, is_old, e);
  mutt_file_fclose(&fp);
  return e;
}

static void maildir_delayed_parsing(struct Mailbox *m, struct MdEmailArray *mda, struct Progress *progress)
{
  char fn[PATH_MAX];

#ifdef USE_HCACHE
  struct HeaderCache *hc = mutt_hcache_open(C_HeaderCache, mailbox_path(m), NULL);
#endif

  struct MdEmail *md = NULL;
  struct MdEmail **mdp = NULL;
  ARRAY_FOREACH(mdp, mda)
  {
    md = *mdp;
    if (!md || !md->email || md->header_parsed)
      continue;

    if (m->verbose && progress)
      mutt_progress_update(progress, ARRAY_FOREACH_IDX, -1);

    snprintf(fn, sizeof(fn), "%s/%s", mailbox_path(m), md->email->path);

#ifdef USE_HCACHE
    struct stat lastchanged = { 0 };
    int rc = 0;
    if (C_MaildirHeaderCacheVerify)
    {
      rc = stat(fn, &lastchanged);
    }

    const char *key = md->email->path + 3;
    size_t keylen = maildir_hcache_keylen(key);
    struct HCacheEntry hce = mutt_hcache_fetch(hc, key, keylen, 0);

    if (hce.email && (rc == 0) && (lastchanged.st_mtime <= hce.uidvalidity))
    {
      hce.email->edata = maildir_edata_new();
      hce.email->edata_free = maildir_edata_free;
      hce.email->old = md->email->old;
      hce.email->path = mutt_str_dup(md->email->path);
      email_free(&md->email);
      md->email = hce.email;
      maildir_parse_flags(md->email, fn);
    }
    else
#endif
    {
      if (maildir_parse_message(m->type, fn, md->email->old, md->email))
      {
        md->header_parsed = true;
#ifdef USE_HCACHE
        key = md->email->path + 3;
        keylen = maildir_hcache_keylen(key);
        mutt_hcache_store(hc, key, keylen, md->email, 0);
#endif
      }
      else
        email_free(&md->email);
    }
  }
#ifdef USE_HCACHE
  mutt_hcache_close(hc);
#endif
}

int maildir_move_to_mailbox(struct Mailbox *m, struct MdEmailArray *mda)
{
  if (!m)
    return 0;

  int oldmsgcount = m->msg_count;

  struct MdEmail *md = NULL;
  struct MdEmail **mdp = NULL;
  ARRAY_FOREACH(mdp, mda)
  {
    md = *mdp;
    mutt_debug(LL_DEBUG2, "Considering %s\n", NONULL(md->canon_fname));
    if (!md->email)
      continue;

    mutt_debug(LL_DEBUG2, "Adding header structure. Flags: %s%s%s%s%s\n",
               md->email->flagged ? "f" : "", md->email->deleted ? "D" : "",
               md->email->replied ? "r" : "", md->email->old ? "O" : "",
               md->email->read ? "R" : "");
    if (m->msg_count == m->email_max)
      mx_alloc_memory(m);

    m->emails[m->msg_count] = md->email;
    m->emails[m->msg_count]->index = m->msg_count;
    mailbox_size_add(m, md->email);

    md->email = NULL;
    m->msg_count++;
  }

  int num = 0;
  if (m->msg_count > oldmsgcount)
    num = m->msg_count - oldmsgcount;

  maildirarray_clear(mda);
  return num;
}

static int maildir_parse_dir(struct Mailbox *m, struct MdEmailArray *mda, const char *subdir, struct Progress *progress)
{
  struct dirent *de = NULL;
  int rc = 0;
  bool is_old = false;
  struct MdEmail *entry = NULL;
  struct Email *e = NULL;

  struct Buffer *buf = mutt_buffer_pool_get();

  mutt_buffer_printf(buf, "%s/%s", mailbox_path(m), subdir);
  is_old = C_MarkOld ? mutt_str_equal("cur", subdir) : false;

  DIR *dirp = opendir(mutt_b2s(buf));
  if (!dirp)
  {
    rc = -1;
    goto cleanup;
  }

  while (((de = readdir(dirp))) && (SigInt != 1))
  {
    if (*de->d_name == '.')
      continue;

    /* FOO - really ignore the return value? */
    mutt_debug(LL_DEBUG2, "queueing %s\n", de->d_name);

    e = email_new();
    e->edata = maildir_edata_new();
    e->edata_free = maildir_edata_free;

    e->old = is_old;
    maildir_parse_flags(e, de->d_name);

    if (m->verbose && progress)
      mutt_progress_update(progress, ARRAY_SIZE(mda) + 1, -1);

    mutt_buffer_printf(buf, "%s/%s", subdir, de->d_name);
    e->path = mutt_buffer_strdup(buf);

    entry = maildir_entry_new();
    entry->email = e;
    ARRAY_ADD(mda, entry);
  }

  closedir(dirp);

  if (SigInt == 1)
  {
    SigInt = 0;
    return -2; /* action aborted */
  }

  static cleanup : mutt_buffer_pool_release(&buf);

  return rc;
}

static int maildir_read_dir(struct Mailbox *m, const char *subdir)
{
  if (!m)
    return -1;

  struct Progress progress;

  if (m->verbose)
  {
    char msg[PATH_MAX];
    snprintf(msg, sizeof(msg), _("Scanning %s..."), mailbox_path(m));
    mutt_progress_init(&progress, msg, MUTT_PROGRESS_READ, 0);
  }

  struct MaildirMboxData *mdata = maildir_mdata_get(m);
  if (!mdata)
  {
    mdata = maildir_mdata_new();
    m->mdata = mdata;
    m->mdata_free = maildir_mdata_free;
  }

  struct MdEmailArray mda = ARRAY_HEAD_INITIALIZER;
  if (maildir_parse_dir(m, &mda, subdir, &progress) < 0)
    return -1;

  if (m->verbose)
  {
    char msg[PATH_MAX];
    snprintf(msg, sizeof(msg), _("Reading %s..."), mailbox_path(m));
    mutt_progress_init(&progress, msg, MUTT_PROGRESS_READ, ARRAY_SIZE(&mda));
  }
  maildir_delayed_parsing(m, &mda, &progress);

  maildir_move_to_mailbox(m, &mda);

  if (!mdata->mh_umask)
    mdata->mh_umask = mh_umask(m);

  return 0;
}

int main(int argc, char *argv[])
{
  const char *dir = "/home/mail/linode/neo";

  if (argc == 2)
    dir = argv[1];

  printf("reading: %s\n", dir);
  struct Mailbox *m = mailbox_new();
  m->type = MUTT_MAILDIR;

  mutt_buffer_strcpy(&m->pathbuf, dir);

  int rc = maildir_read_dir(m, "cur");
  printf("rc = %d\n", rc);

  for (int i = 0; i < m->email_max; i++)
  {
    struct Email *e = m->emails[i];
    struct MaildirEmailData *edata = maildir_edata_get(e);
    if (!e || !edata)
      continue;
    // printf("%10ld %s\n", edata->inode, e->path);
    printf("%s\n", e->path);
  }

  mailbox_free(&m);
  return 0;
}
