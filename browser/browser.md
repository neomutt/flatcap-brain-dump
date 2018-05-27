# Fixing NeoMutt's Browser

## Discussions

I suggest we try, as much as possible to focus our work on browser.c/h and not
altering the code of any other file. This way, we can work in a specific branch and have a specific
architecture in the file that will merge more efficiently. Then, when we merge, we can split the content
of the file into many smaller files if that is relevant, of course.

Yes, or a separate file completely.  New file, new history.

Ah, that's a nice suggestion!

Then as it matures, we can change one user of the old browser to the improved browser.

## Goals, ideas

In a new file/directory, rebuild a clean browser application for mutt.

1. Keep all functionalities of the current mutt browser
2. Refactor all the code to get something coherent.
3. Get rid of as much ifdef as possible (being meta is the key)
4. The browser is a browser, it doesn't give any signification to its display.
     It displays and select, that's all.
5. Get coherent key bindings
6. It has features (sorting, listing, unselectable entries, tagging, …)
7. mutt\_select\_file or else are browsing functions, but high-level ones,
     these functions are specific and should be defined to rely on more basic functions
     of the browser. That would reduce the redundancy in the code.

## Current Browsers

Below are all the ways in which NeoMutt browses things.

### Shared Fields

* **%>X** right justify
* **%|X** pad to the end of the line
* **%*X** soft-fill

### Address Browser

Allow the user to select an address (from an external query).
**Note**: There is no sorting option

#### Options

* NONE

#### Functions

* "A" query-append
* "Q" query
* "a" create-alias
* "m" mail

#### Fields for $query\_format

* **%a** destination address
* **%c** current entry number
* **%e** extra information
* **%n** destination name
* **%t** tagged?

### Alias Browser

Allow the user to select an alias.
**Note**: There is no sorting option

#### Options

* NONE

#### Functions

* <Enter>  select-entry
* <Return> select-entry
* <Space>  tag-entry
* "d"      delete-entry
* "u"      undelete-entry

#### Fields for $alias\_format

* **%a** alias name
* **%f** flags
* **%n** index number
* **%r** address which alias expands to
* **%t** tagged?

### Attachment Browser

Allow the user to select an attachment.
**Note:** Many of the functions apply to the email, not the attachment.

#### Options

* NONE

#### Functions

* "^D"       toggle-disposition
* "^E"       edit-encoding
* "^F"       forget-passphrase
* "<Enter>"  view-attach
* "<Return>" view-attach
* "^O"       rename-attachment
* "^T"       edit-type
* "^Xe"      edit-file
* "<Esc>f"   edit-from
* "<Esc>k"   attach-key
* "A"        attach-message
* "C"        copy-file
* "D"        detach-file
* "E"        edit-headers
* "F"        filter-entry
* "G"        get-attachment
* "P"        postpone-message
* "R"        rename-file
* "S"        smime-menu
* "T"        tag-entry
* "U"        update-encoding
* "a"        attach-file
* "b"        edit-bcc
* "c"        edit-cc
* "d"        edit-description
* "e"        edit-message
* "f"        edit-fcc
* "h"        display-toggle-weed
* "i"        ispell
* "l"        print-entry
* "m"        edit-mime
* "n"        new-mime
* "p"        pgp-menu
* "r"        edit-reply-to
* "s"        edit-subject
* "t"        edit-to
* "u"        toggle-unlink
* "w"        write-fcc
* "y"        send-message
* "|"        pipe-entry

#### Fields for $attach\_format

* **%C** charset
* **%c** requires charset conversion
* **%D** deleted flag
* **%d** description
* **%e** MIME content-transfer-encoding
* **%F** filename in content-disposition header
* **%f** filename
* **%I** disposition
* **%m** major MIME type
* **%M** MIME subtype
* **%n** attachment number
* **%Q** qualifies for attachment counting
* **%s** size
* **%t** tagged flag
* **%T** graphic tree characters
* **%u** unlink (=to delete) flag
* **%X** number of MIME parts

### Filesystem Browser

Allow the user to select a file or directory.

#### Options

* Select file only
* Select dir only
* Select file or dir
* Show hidden files/dirs
* Single selection
* Multiple selections
* File mask (filtering)
* Sorting

#### Functions

* <Tab>   toggle-mailboxes
* <Space> view-file
* "."     buffy-list
* "="     goto-folder
* "@"     display-filename
* "C"     create-mailbox
* "N"     select-new
* "O"     sort-reverse
* "T"     toggle-subscribed (IMAP)
* "c"     change-dir
* "d"     delete-mailbox (IMAP)
* "m"     enter-mask
* "o"     sort
* "r"     rename-mailbox (IMAP)
* "s"     subscribe (IMAP/NNTP)
* "u"     unsubscribe (IMAP/NNTP)
* "y"     exit

#### Fields for $folder\_format

* **%C** current file number
* **%d** date/time folder was last modified
* **%D** date/time folder was last modified using $date\_format.
* **%F** file permissions
* **%f** filename (with suffix [/@*])
* **%g** group name (or numeric gid, if missing)
* **%l** number of hard links
* **%m** number of messages in the mailbox
* **%N** N if mailbox has new mail, blank otherwise
* **%n** number of unread messages in the mailbox
* **%s** size in bytes
* **%t** "*" if the file is tagged, blank otherwise
* **%u** owner name (or numeric uid, if missing)

### Mailbox Browser

Allow the user to select a network mailbox.
**Note**: Currently, this uses $folder\_format.

#### Options

* Sorting
* Toggle between mailbox and filesystem views

#### Functions

* <Tab>   toggle-mailboxes
* <Space> view-file
* "."     buffy-list
* "="     goto-folder
* "@"     display-filename
* "C"     create-mailbox
* "N"     select-new
* "O"     sort-reverse
* "T"     toggle-subscribed (IMAP)
* "c"     change-dir
* "d"     delete-mailbox (IMAP)
* "m"     enter-mask
* "o"     sort
* "r"     rename-mailbox (IMAP)
* "s"     subscribe (IMAP/NNTP)
* "u"     unsubscribe (IMAP/NNTP)
* "y"     exit

#### Fields for $folder\_format

* **%C** current file number
* **%d** date/time folder was last modified
* **%D** date/time folder was last modified using $date\_format.
* **%F** file permissions
* **%f** filename (with suffix [/@*])
* **%g** group name (or numeric gid, if missing)
* **%l** number of hard links
* **%m** number of messages in the mailbox
* **%N** N if mailbox has new mail, blank otherwise
* **%n** number of unread messages in the mailbox
* **%s** size in bytes
* **%t** "*" if the file is tagged, blank otherwise
* **%u** owner name (or numeric uid, if missing)

### Message Browser

Allow the user to select a message, e.g. for attaching.
**Note**: This spawns a the main index, so the list of possible functions is huge.

#### Options

* Sorting

#### Functions

* "^D"         delete-thread
* "^E"         edit-type
* "^F"         forget-passphrase
* "<Tab>"      next-new-then-unread
* "<Enter>"    display-message
* "^K"         extract-keys
* "<Return>"   display-message
* "^N"         sidebar-next
* "^O"         sidebar-open
* "^P"         sidebar-prev
* "^R"         read-thread
* "^T"         untag-pattern
* "^U"         undelete-thread
* "<Esc><Tab>" previous-new-then-unread
* "<Esc>P"     check-traditional-pgp
* "<Esc>V"     collapse-all
* "<Esc>c"     change-folder-readonly
* "<Esc>d"     delete-subthread
* "<Esc>e"     resend-message
* "<Esc>k"     mail-key
* "<Esc>l"     show-limit
* "<Esc>n"     next-subthread
* "<Esc>p"     previous-subthread
* "<Esc>r"     read-subthread
* "<Esc>s"     decode-save
* "<Esc>t"     tag-thread
* "<Esc>u"     undelete-subthread
* "<Esc>v"     collapse-thread
* "<Space>"    display-message
* "#"          break-thread
* "$"          sync-mailbox
* "%"          toggle-write
* "\&"          link-threads
* "."          buffy-list
* "@"          display-address
* "C"          copy-message
* "D"          delete-pattern
* "F"          flag-message
* "G"          imap-fetch-mail
* "J"          next-entry
* "C"          copy-message
* "D"          delete-pattern
* "F"          flag-message
* "G"          imap-fetch-mail
* "J"          next-entry
* "K"          previous-entry
* "L"          list-reply
* "N"          toggle-new
* "O"          sort-reverse
* "P"          parent-message
* "Q"          query
* "R"          recall-message
* "T"          tag-pattern
* "U"          undelete-pattern
* "V"          show-version
* "W"          clear-flag
* "Y"          edit-label
* "a"          create-alias
* "b"          bounce-message
* "c"          change-folder
* "d"          delete-message
* "e"          edit
* "f"          forward-message
* "g"          group-reply
* "h"          display-toggle-weed
* "j"          next-undeleted
* "k"          previous-undeleted
* "l"          limit
* "m"          mail
* "o"          sort-mailbox
* "p"          print-message
* "q"          quit
* "r"          reply
* "s"          save-message
* "u"          undelete-message
* "v"          view-attachments
* "w"          set-flag
* "x"          exit
* "|"          pipe-message
* "~"          mark-message
* "<Down>"     next-undeleted
* "<Up>"       previous-undeleted

#### Fields for $index\_format

* **%a** address of the author
* **%A** reply-to address
* **%b** filename of the message folder
* **%B** the list to which the letter was sent
* **%c** number of characters (bytes) in the message
* **%C** current message number
* **%d** date and time of the message in sender's time zone
* **%D** date and time of the message in the local time zone
* **%e** current message number in thread
* **%E** number of messages in current thread
* **%f** sender (address + real name)
* **%F** author name, or recipient name
* **%g** message labels
* **%H** spam attribute(s)
* **%I** initials of author
* **%i** message-id of the current message
* **%K** the list to which the letter was sent
* **%l** number of lines in the message
* **%L** "To <list-name>"
* **%m** total number of message in the mailbox
* **%M** number of hidden messages
* **%N** message score
* **%n** author's real name
* **%O** original save folder
* **%P** progress indicator for the built-in pager
* **%q** newsgroup name
* **%r** list of "To:" recipients
* **%R** list of "Cc:" recipients
* **%s** subject of the message
* **%S** single character status of the message
* **%t** "To:" field
* **%T** character from the $to\_chars string
* **%u** user (login) name of the author
* **%v** first name of the author
* **%W** name of organization of author
* **%x** "X-Comment-To:" field
* **%X** number of attachments
* **%y** "X-Label:" field, if present
* **%Y** "X-Label:" field, if present
* **%Z** a three character set of message status flags.
* **%zs** message status flags
* **%zc** message crypto flags
* **%zt** message tag flags
* **%{fmt}** date and time of the message is converted to sender's time zone
* **%[fmt]** date and time of the message is converted to the local time zone
* **%(fmt)** local date and time when the message was received.
* **%<fmt>** current local time

### PGP Key Browser

Allow the user to select a PGP key.
**Note**: There is no sorting option

#### Options

* NONE

#### Functions

* "%" view-name
* "c" verify-key

#### Fields for $pgp\_entry\_format

* **%a** algorithm
* **%c** capabilities
* **%f** flags
* **%k** key id
* **%l** key length
* **%n** number
* **%p** protocol
* **%t** trust/validity
* **%u** user id
* **%[]** date of the key

## Design Decisions

### What do we want to display?

* List of single-line items
  - Simple *Mutt*-like
  - Use format string
* List of multi-line items
  - e.g. PGP keys (may need variable number of lines):
    * Name <email>
    * Expiry, validity, etc
  - Formatting string
    * One with embedded '\n'
    * Two, second is optional
  - Colouring
    * One.  Coloured by field
    * Two, second is optional
  - Does selection highlight first line, or all lines?
    * Depends on the caller, then can mark lines selectable
  - Do we display partial multi-line rows?
* Header Row
  - Use format string to arrange header in the order of the fields
  - Highlighting of Header Row field could indicate sort field
* Separators
  - Blank - for visual clarity
  - Titled - for distinguishing groups of data
  - Inserted by the code, not the user 

### How do we want to display lines?

* Flat list
  - Simple, understandable
* Nested
  - Shallow, 1 or 2 levels of nesting
  - Deep: show entire tree
    * Threaded emails
    * Nested mime attachments
* Paged
  - Display entire list
    * Caller must *have *the entire list first
    * For large mailboxes, this could be many thousands of items
  - Display subset of list
    * Caller can prepare the visible list as needed
    * Need clear visual feedback when the list is incomplete
    * How is sorting handled?

### What does the Browser know about the lines?

* Nothing
  - Browser has ordered list of items
  - Caller has formatted them
  - Caller has themed them
  - Some are selectable
* Knows about separate fields and their types
  - Browser could offer sorting

### How do we style the Browser?

Attributes: foreground colour, background colour, style, e.g. underline

* Browser
  - Panel.  Default colours for the entire panel
  - Header row (if handled by the browser)
    * Normal
    * Sort field
  - Selection
    * Current selection
    * Cursor position
    * Tagged (if handled by the browser)
* Line
  - Caller sets attributes for the entire (multi-)line
  - Caller sets attributes per line (or sub-line)
* Field
  - Caller sets attributes for an entire field
  - Caller sets attributes for part(s) of a field
* Search
  - Highlight a matching search field (even if the string isn't visible on screen)

### Folding Nested Items

* Fold levels:
  - Default fold level (like vim)
  - Open/close folds manually
  - All open by default?
  - Caller dependent
* What can we fold?
  - nested items, e.g. directories
  - multiline rows, e.g. pgp keys
* Need clear visual feedback

### Search/Limit API

If the browser doesn't know about fields, then the searching needs to be done by the caller.

* Search
  - On full fields (the on-screen fields might be truncated)
  - Search in either direction
  - Optionally wrap around
* Highlight
  - Optional
  - Highlight entire matching field (especially if the field is truncated)
  - Highlight match within a field
  - Matches:
    * No highlight, just move the cursor
    * Highlight current match
    * Highlight all matches (like vim's hlsearch)
* Limit
  - Like search
  - Optional highlighting of fields
  - Caller hides non-matching rows

**Example: **Search for 'the'

* Highlight field
  - Match visible: "weather"
  - Match not visible: "today's wea"
* Sub-field
  - Match visible: "weather"

## Glossary

* **attributes** - underline, bold, reverse, etc
* **browser** - select from a _list_ of _items_, displayed as _rows_
* **caller** - code that creates the _entries_ and handles callbacks from the _browser_
* **colour** - foreground, background
* **column** - same _field_ of multiple _items_ in a _list_
* **cursor** - currently selected _item_
* **entry/ies** - object representing one _item_
* **field** - piece of data belonging to an _item_
* **header** - non-selectable _row_ in the _browser_
* **hidden** - _item_ in _list_ that shouldn't be displayed
* **item** - object (in a _list_) to be selected
* **line** - one screen line, see _row_ 
* **list** - collection of _items_
* **panel** - window containing the _browser_
* **row** - one _item_ on screen, may use several _lines_
* **selection** - the chosen _item_
* **separator** - a non-selectable _line_ in the _list_
* **style** - _colour_ or _attributes_
* **visible** - _item_ in _list_ that shouldn't be displayed

```
╭─────────────┬───────────────────────────────────────────────────────────────────╮
│ Header      │ Column1  Column2         Column3            Column4               │
│             ├───────────────────────────────────────────────────────────────────┤
             
│             ├───────────────────────────────────────────────────────────────────┤
│ Simple Row  │Field1    Field2          Field3             Field4                │
│             ├───────────────────────────────────────────────────────────────────┤
             
│             ├───────────────────────────────────────────────────────────────────┤
│ Complex Row │Field1    Field2          Field3             Field4                │
│  2nd line   │    Some other formatted data                                      │
│  3rd line   │    More data still                                                │
│             ├───────────────────────────────────────────────────────────────────┤
```

