struct Address;
struct Body;
struct Email;
struct EnterState;
struct Envelope;
struct Keymap;
struct Pager;
struct Pattern;
struct KeyEvent
{
  int ch;
  int op;
};
bool g_addr_is_user = false;
int g_body_parts = 1;
bool g_is_mail_list = false;
bool g_is_subscribed_list = false;
const char *g_myvar = "hello";
short AbortKey;
typedef uint8_t MuttFormatFlags;
typedef uint16_t CompletionFlags;
typedef uint16_t PagerFlags;
typedef uint8_t SelectFileFlags;
typedef const char *(format_t) (char *buf, size_t buflen, size_t col, int cols, char op, const char *src, const char *prec, const char *if_str, const char *else_str, intptr_t data, MuttFormatFlags flags);
struct Address *alias_reverse_lookup(const struct Address *addr)
{
  return NULL;
}
int crypt_valid_passphrase(int flags)
{
  return 0;
}
bool imap_search(struct Mailbox *m, const struct Pattern *pat)
{
  return false;
}
bool mutt_addr_is_user(struct Address *addr)
{
  return g_addr_is_user;
}
struct Address *mutt_alias_reverse_lookup(struct Address *a)
{
  return NULL;
}
int mutt_body_handler(struct Body *b, struct State *s)
{
  return -1;
}
void mutt_clear_error(void)
{
}
int mutt_copy_header(FILE *in, struct Email *e, FILE *out, int flags, const char *prefix)
{
  return -1;
}
int mutt_count_body_parts(struct Mailbox *m, struct Email *e, struct Message *msg)
{
  return g_body_parts;
}
bool mutt_is_mail_list(struct Address *addr)
{
  return g_is_mail_list;
}
bool mutt_is_subscribed_list(struct Address *addr)
{
  return g_is_subscribed_list;
}
void mutt_parse_mime_message(struct Mailbox *m, struct Email *e, FILE *msg)
{
}
void mutt_str_pretty_size(char *buf, size_t buflen, size_t num)
{
}
void mutt_set_flag_update(struct Mailbox *m, struct Email *e, int flag, bool bf, bool upd_mbox)
{
}
int mx_msg_close(struct Mailbox *m, struct Message **msg)
{
  return 0;
}
struct Message *mx_msg_open(struct Mailbox *m, int msgno)
{
  return NULL;
}
int mx_msg_padding_size(struct Mailbox *m)
{
  return 0;
}
const char *myvar_get(const char *var)
{
  return g_myvar;
}
struct Email *mutt_get_virt_email(struct Mailbox *m, int vnum)
{
  if (!m || !m->emails || !m->v2r)
    return NULL;
  if ((vnum < 0) || (vnum >= m->vcount))
    return NULL;
  int inum = m->v2r[vnum];
  if ((inum < 0) || (inum >= m->msg_count))
    return NULL;
  return m->emails[inum];
}
void mutt_buffer_mktemp_full(struct Buffer *buf, const char *prefix, const char *suffix, const char *src, int line)
{
}
int mutt_rfc822_write_header(FILE *fp, struct Envelope *env, struct Body *attach, int mode, bool privacy, bool hide_protected_subject)
{
  return 0;
}
void mutt_expando_format(char *buf, size_t buflen, size_t col, int cols, const char *src, format_t *callback, intptr_t data, MuttFormatFlags flags)
{
}
struct Menu *menu_new(enum MenuType type)
{
  return mutt_mem_calloc(1, sizeof(struct Menu));
}
void menu_pop_current(struct Menu *menu)
{
}
int menu_loop(struct Menu *menu)
{
  return 0;
}
void menu_current_redraw(void)
{
}
int mutt_enter_string_full(char *buf, size_t buflen, int col, CompletionFlags flags, bool multiple, char ***files, int *numfiles, struct EnterState *state)
{
  return 0;
}
void mutt_resize_screen(void)
{
}
void menu_push_current(struct Menu *menu)
{
}
int km_expand_key(char *s, size_t len, struct Keymap *map)
{
  return 0;
}
struct Keymap *km_find_func(enum MenuType menu, int func)
{
  return NULL;
}
struct EnterState *mutt_enter_state_new(void)
{
  return NULL;
}
void mutt_enter_state_free(struct EnterState **ptr)
{
}
void menu_free(struct Menu **ptr)
{
  FREE(ptr);
}
int mutt_pager(const char *banner, const char *fname, PagerFlags flags, struct Pager *extra)
{
  return 0;
}
int mutt_monitor_poll(void)
{
  return 0;
}
int mutt_system(const char *cmd)
{
  return 0;
}
void mutt_buffer_select_file(struct Buffer *file, SelectFileFlags flags, char ***files, int *numfiles)
{
}
struct Mailbox *mview_mailbox(struct MailboxView *mv)
{
  return mv ? mv->mailbox : NULL;
}
int menu_get_index(struct Menu *menu)
{
  return -1;
}
MenuRedrawFlags menu_set_index(struct Menu *menu, int index)
{
  return true;
}
