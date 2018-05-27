## Unsorted Notes

We want a standard way to interact with a list of objects.

There's a big overlap between the:

* "browser" allows the user to select a mailbox or a file
* "menu" allows the user to select a key, an alias

[`browser.c`](url{https://github.com/neomutt/neomutt/blob/master/browser.c)}
has over 50 `#ifdef`s There are significant amounts of imap, nntp and
notmuch code in it (and 1/3 of imap's ifdefs).

The browser shouldn't know what it's displaying.

Browser needs a format_string

* default behaviour/expandos for padding, etc
* overrides for caller-specific fields

Browser needs navigation keys

* defaults - up, down, select, etc
* override - for caller-specific actions
* needs to tie these into the help line

Browser needs colours

* default - app-wide indicator, highlight, etc
* override - caller-specific colours

Browser's list attributes

* selection mode: 1, many (tagging)
* callback(s) for events, keys, etc
* display title/header line?

Browser obj has

* (optional) list of column names
* (list of) callback(s)

Browser item attributes

* item is (in)visible
* item is (un)selectable
* item is selectED (perhaps to prepopulate a list)
* sequence number: for "unsorting" a list

Browser callback for actions

* SELECTION_CHANGED
* KEYPRESS (allowing override)
* WINCH? (window resized?)

Keypress callback returns

* HANDLED
* NOT_HANDLED
* ACTION_X?
  - isn't that the same as NOT_HANDLED?
  - X = browser default behaviours

API for caller to manipulate browser

* no callbacks during API usage?
* opaque pointer to browser data

Item types (things in a browser list)

* data
* title/header (need colour)
* separator (need colour)

sorting callback

* build in some defaults? (+reverse)
* ascii
* numeric
* date
* how do we select a field generically?

Requirements from mutt

* MuttWindow
* WINCH from getch()
* colours
* some global variables

Consider lua integration

* if exists DOMAIN_browser()? call it
* else call code callback?
* pass lua array (or same opaque ptr)

lua_init: register callback for DOMAIN_browser?

Who handles toggle mailboxes/files

able to enter directories e.g.

* imap INBOX
* maildir cur

mutt_select_file()
mutt_enter_fname()

action on timeout/hooks?
notification of buffy changes
status bar notifications

* "you're in the browser"
* or a helpline title?

how does the help page know the keybindings?

* generic list, it's not smart

var $debug_use_new_browser
new browser can be enabled piecemeal (one caller at a time)

external formatting
external colouring
should the browser know about columns, or just rows
column headings could indicate sort order
headings => browser is aware of columns/fields
unless external header drawing
external colouring needs to be able to colour entire line
-> allows "color ~T" and other custom colours

is limiting done by the browser or the caller?
probably the caller.  the browser doesn't understand the data
caller can mark entries "hidden" to filter

multi-line: do we store the "sub-lines" as children?
(just like nesting)
probably simpler for sorting purposes

keep raw fields in the browser entries for searching purposes
allow the browser to search?
it would need to understand field types (unless we coerce all the types to string)

