
<details>
<summary>struct MailboxView</summary>

https://github.com/neomutt/neomutt/blob/d67c876ae5411781bf2240289fd7abc97cd002f4/mview.h#L37-L51
</details>

<details>
<summary>struct Mailbox</summary>

https://github.com/neomutt/neomutt/blob/d67c876ae5411781bf2240289fd7abc97cd002f4/core/mailbox.h#L78-L146
</details>

<details>
<summary>struct ThreadsContext</summary>

https://github.com/neomutt/neomutt/blob/d67c876ae5411781bf2240289fd7abc97cd002f4/mutt_thread.c#L49-L56
</details>

<details>
<summary>struct MuttThread</summary>

https://github.com/neomutt/neomutt/blob/d67c876ae5411781bf2240289fd7abc97cd002f4/email/thread.h#L34-L52
</details>

<details>
<summary>struct Email</summary>

https://github.com/neomutt/neomutt/blob/d67c876ae5411781bf2240289fd7abc97cd002f4/email/email.h#L36-L125
</details>

<details>
<summary>struct MailboxView</summary>

```c
struct MailboxView
{
  off_t vsize;                       ///< Size (in bytes) of the messages shown
  char *pattern;                     ///< Limit pattern string
  struct PatternList *limit_pattern; ///< Compiled limit pattern
  struct ThreadsContext *threads;    ///< Threads context
  int msg_in_pager;                  ///< Message currently shown in the pager
  struct Menu *menu;                 ///< Needed for pattern compilation
  bool collapsed : 1;                ///< Are all threads collapsed?
  struct Mailbox *mailbox;           ///< Current Mailbox
  struct Notify *notify;             ///< Notifications: #NotifyMview, #EventMview
};
```
</details>

<details>
<summary>struct Mailbox</summary>

```c
struct Mailbox
{
  struct Buffer pathbuf;              ///< Path of the Mailbox
  char *realpath;                     ///< Used for duplicate detection, context comparison, and the sidebar
  char *name;                         ///< A short name for the Mailbox
  struct ConfigSubset *sub;           ///< Inherited config items
  off_t size;                         ///< Size of the Mailbox
  bool has_new;                       ///< Mailbox has new mail
  int msg_count;                      ///< Total number of messages
  int msg_unread;                     ///< Number of unread messages
  int msg_flagged;                    ///< Number of flagged messages
  int msg_new;                        ///< Number of new messages
  int msg_deleted;                    ///< Number of deleted messages
  int msg_tagged;                     ///< How many messages are tagged?
  struct Email **emails;              ///< Array of Emails
  int email_max;                      ///< Number of pointers in emails
  int *v2r;                           ///< Mapping from virtual to real msgno
  int vcount;                         ///< The number of virtual messages
  bool notified;                      ///< User has been notified
  enum MailboxType type;              ///< Mailbox type
  bool newly_created;                 ///< Mbox or mmdf just popped into existence
  struct timespec mtime;              ///< Time Mailbox was last changed
  struct timespec last_visited;       ///< Time of last exit from this mailbox
  const struct MxOps *mx_ops;         ///< MXAPI callback functions
  bool append                 : 1;    ///< Mailbox is opened in append mode
  bool changed                : 1;    ///< Mailbox has been modified
  bool dontwrite              : 1;    ///< Don't write the mailbox on close
  bool first_check_stats_done : 1;    ///< True when the check have been done at least on time
  bool peekonly               : 1;    ///< Just taking a glance, revert atime
  bool verbose                : 1;    ///< Display status messages?
  bool readonly               : 1;    ///< Don't allow changes to the mailbox
  AclFlags rights;                    ///< ACL bits, see #AclFlags
  void *compress_info;                ///< Compressed mbox module private data
  struct HashTable *id_hash;          ///< Hash Table by msg id
  struct HashTable *subj_hash;        ///< Hash Table by subject
  struct HashTable *label_hash;       ///< Hash Table for x-labels
  struct Account *account;            ///< Account that owns this Mailbox
  int opened;                         ///< Number of times mailbox is opened
  bool visible;                       ///< True if a result of "mailboxes"
  void *mdata;                        ///< Driver specific data
  void (*mdata_free)(void **ptr);
  struct Notify *notify;              ///< Notifications: #NotifyMailbox, #EventMailbox
  int gen;                            ///< Generation number, for sorting
};
```
</details>

<details>
<summary>struct ThreadsContext</summary>

```c
struct ThreadsContext
{
  struct Mailbox *mailbox; ///< Current mailbox
  struct MuttThread *tree; ///< Top of thread tree
  struct HashTable *hash;  ///< Hash table of Email subjects
  short c_sort;            ///< Last sort method
  short c_sort_aux;        ///< Last sort_aux method
};
```
</details>

<details>
<summary>struct MuttThread</summary>

```c
struct MuttThread
{
  bool fake_thread             : 1; ///< Emails grouped by Subject
  bool duplicate_thread        : 1; ///< Duplicated Email in Thread
  bool sort_children           : 1; ///< Sort the children
  bool check_subject           : 1; ///< Should the Subject be checked?
  bool visible                 : 1; ///< Is this Thread visible?
  bool deep                    : 1; ///< Is the Thread deeply nested?
  unsigned int subtree_visible : 2; ///< Is this Thread subtree visible?
  bool next_subtree_visible    : 1; ///< Is the next Thread subtree visible?
  struct MuttThread *parent;        ///< Parent of this Thread
  struct MuttThread *child;         ///< Child of this Thread
  struct MuttThread *next;          ///< Next sibling Thread
  struct MuttThread *prev;          ///< Previous sibling Thread
  struct Email *message;            ///< Email this Thread refers to
  struct Email *sort_thread_key;    ///< Email that controls how top thread sorts
  struct Email *sort_aux_key;       ///< Email that controls how subthread siblings sort
};
```
</details>

<details>
<summary>struct Email</summary>

```c
struct Email
{
  // Data that gets stored in the Header Cache
  SecurityFlags security;      ///< bit 0-10: flags, bit 11,12: application, bit 13: traditional pgp
  bool expired    : 1;         ///< Already expired?
  bool flagged    : 1;         ///< Marked important?
  bool mime       : 1;         ///< Has a MIME-Version header?
  bool old        : 1;         ///< Email is seen, but unread
  bool read       : 1;         ///< Email is read
  bool replied    : 1;         ///< Email has been replied to
  bool superseded : 1;         ///< Got superseded?
  bool trash      : 1;         ///< Message is marked as trashed on disk (used by the maildir_trash option)
  unsigned int zhours   : 5;   ///< Hours away from UTC
  unsigned int zminutes : 6;   ///< Minutes away from UTC
  bool zoccident        : 1;   ///< True, if west of UTC, False if east
  time_t date_sent;            ///< Time when the message was sent (UTC)
  time_t received;             ///< Time when the message was placed in the mailbox
  int lines;                   ///< How many lines in the body of this message?

  // Management data - Runtime info and glue to hold the objects together
  size_t sequence;             ///< Sequence number assigned on creation
  struct Envelope *env;        ///< Envelope information
  struct Body *body;           ///< List of MIME parts
  char *path;                  ///< Path of Email (for local Mailboxes)
  LOFF_T offset;               ///< Where in the stream does this message begin?
  struct TagList tags;         ///< For drivers that support server tagging
  struct Notify *notify;       ///< Notifications: #NotifyEmail, #EventEmail
  void *edata;                 ///< Driver-specific data
  bool active          : 1;    ///< Message is not to be removed
  bool changed         : 1;    ///< Email has been edited
  bool deleted         : 1;    ///< Email is deleted
  bool purge           : 1;    ///< Skip trash folder when deleting
  void (*edata_free)(void **ptr); ///< Free the private data attached to the Email
  struct ListHead chain;       ///< Mixmaster chain
  void *nm_edata;              ///< Notmuch private data

  // View data - Used by the GUI
  bool attach_del      : 1;    ///< Has an attachment marked for deletion
  bool attach_valid    : 1;    ///< true when the attachment count is valid
  bool display_subject : 1;    ///< Used for threading
  bool matched         : 1;    ///< Search matches this Email
  bool quasi_deleted   : 1;    ///< Deleted from neomutt, but not modified on disk
  bool recip_valid     : 1;    ///< Is_recipient is valid
  bool searched        : 1;    ///< Email has been searched
  bool subject_changed : 1;    ///< Used for threading
  bool tagged          : 1;    ///< Email is tagged
  bool threaded        : 1;    ///< Used for threading
  int index;                   ///< The absolute (unsorted) message number
  int msgno;                   ///< Number displayed to the user
  struct AttrColor *attr_color; ///< Color-pair to use when displaying in the index
  int score;                   ///< Message score
  int vnum;                    ///< Virtual message number
  short attach_total;          ///< Number of qualifying attachments in message, if attach_valid
  short recipient;             ///< User_is_recipient()'s return value, cached
  struct MuttThread *thread;   ///< Thread of Emails
  bool collapsed : 1;          ///< Is this message part of a collapsed thread?
  bool visible   : 1;          ///< Is this message part of the view?
  bool limit_visited : 1;      ///< Has the limit pattern been applied to this message?
  size_t num_hidden;           ///< Number of hidden messages in this view
  char *tree;                  ///< Character string to print thread tree
};
```
</details>


