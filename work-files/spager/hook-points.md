# Hook points for the Simple Pager

## Help

`void mutt_help(enum MenuType menu)`

### Command

`?` / `<help>`

### Sample Text

```
^D             delete-thread             delete all messages in thread
^E             edit-type                 edit attachment content type

macros:
<Esc>i         open empty inbox
c~/mail/inbox.empty<enter>

,n             T~N\n;WN;t
,o             T~O\n;WO;t

Unbound functions:
autocrypt-acct-menu          manage autocrypt accounts
catchup                      mark all articles in newsgroup as read

Message flags:
set flag_chars = "*!DdrONon- "
    *     message is tagged
    !     message is flagged
```

### Colours

- heading
- keybinding
- function
- macro-text
- description
- stripes
   - stripe-even
   - stripe-odd
- command
- identifier
- description

--------------------------------------------------------------------------------

## Set

`enum CommandResult set_dump(enum GetElemListFlags flags, struct Buffer *err)`

### Command

`:set [all]`

### Sample Text

```
# comment
set index_format      = "string"
set sort              = enum
set ask_bcc           = bool
set pager_index_lines = number
```

### Colours

- comment
- command
- config-option / identifier
- operator / equals
- string
- enum
- number

--------------------------------------------------------------------------------

## Bind

`enum CommandResult dump_bind_macro(struct Buffer *buf, struct Buffer *s, intptr_t data, struct Buffer *err)`
`dump_bind(filebuf, menu_index, buf_string(buf))`

want striping
want auto-column-width, per section

### Command

`:bind`

### Sample Text

```
bind attach    <KeypadEnter> view-attach
bind autocrypt D             delete-account
```

### Colours

- command
- menu
- keybinding
- function

--------------------------------------------------------------------------------

## Macro

`enum CommandResult dump_bind_macro(struct Buffer *buf, struct Buffer *s, intptr_t data, struct Buffer *err)`
`dump_macro(filebuf, menu_index, buf_string(buf))`

### Command

`:macro`

### Sample Text

needs same layout as `<help>` page

```
macro index ,n "T~N\n;WN;t"
macro index ,o "T~O\n;WO;t"
```

### Colours

- command
- menu
- keybinding
- macro-text
- description

--------------------------------------------------------------------------------

## Colour

`void color_dump(void)`

### Command

`:color`

### Sample Text

ansi swatches
need to autosize columns

```
# Simple Colours
color attachment         bold                 brightmagenta    default          # XXXXXX
color bold               bold                 default          default          # XXXXXX
```

### Colours

- comment
- command
- colour object
- attributes
- color
   - color-simple
   - color-palette
   - color-rgb
- ansi swatch
- stripes
   - stripe-even
   - stripe-odd

--------------------------------------------------------------------------------

## Version

`static enum CommandResult parse_version(struct Buffer *buf, struct Buffer *s, intptr_t data, struct Buffer *err)`

### Command

`:version`

### Sample Text

```
NeoMutt 20250109-81-753ae0
Copyright (C) 2015-2025 Richard Russon and friends

Compile options:
  +autocrypt +fcntl -flock +fmemopen +futimens +getaddrinfo +gnutls +gpgme
  -gsasl +gss +hcache -homespool +idn +inotify -locales_hack +lua +nls +notmuch
  -openssl +pcre2 +pgp +sasl +smime +sqlite +truecolor
```

### Colours

- version
- heading
- enabled
- disabled

--------------------------------------------------------------------------------

## Log Messages

`static int op_show_log_messages(int op)`

need to start at bottom of the file

### Command

`M` / `<show-log-messages>`

### Sample Text

```
[15:08:12]<M> Reading /home/mutt/mail/linode/neo/devel...
[15:08:12]<M> Sorting mailbox...
[15:08:12]<1> Got op OP_LIST_REPLY (139)
[15:08:13]<E> No mailing lists found
[15:08:13]<1> unlinking /tmp/mutt/neomutt-flatcap-1001-486207-3039431255855416271
[15:08:13]<1> Handled OP_LIST_REPLY (139) -> error
[15:08:14]<1> Got op OP_SHOW_LOG_MESSAGES (220)
```

### Colours

- debug
- message
- warning
- error
- timestamp

