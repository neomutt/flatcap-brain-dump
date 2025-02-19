// clang-format off
#define MODULE_LIST(_fmt) \
  _fmt(Address)  _fmt(Alias)    _fmt(Attach)   _fmt(Autocrypt) \
  _fmt(Bcache)   _fmt(Browser)  _fmt(Color)    _fmt(Complete)  \
  _fmt(Compmbox) _fmt(Compose)  _fmt(Compress) _fmt(Config)    \
  _fmt(Conn)     _fmt(Convert)  _fmt(Core)     _fmt(Editor)    \
  _fmt(Email)    _fmt(Envelope) _fmt(Expando)  _fmt(Gui)       \
  _fmt(Hcache)   _fmt(Helpbar)  _fmt(History)  _fmt(Imap)      \
  _fmt(Index)    _fmt(Key)      _fmt(Maildir)  _fmt(Mbox)      \
  _fmt(Menu)     _fmt(Mh)       _fmt(Mutt)     _fmt(Ncrypt)    \
  _fmt(Nntp)     _fmt(Notmuch)  _fmt(Pager)    _fmt(Parse)     \
  _fmt(Pattern)  _fmt(Pop)      _fmt(Postpone) _fmt(Progress)  \
  _fmt(Question) _fmt(Send)     _fmt(Sidebar)  _fmt(Store)
// clang-format on

#define DECLARE_MODULES(module) extern struct Module Module##module;

MODULE_LIST(DECLARE_MODULES)

