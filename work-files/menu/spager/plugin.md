# Plugins

Plugins may need to register (and possibly unregister)
- functions
- colours
- commands
- config
each needs (domain/uid)

# Search Plugin (a la quickhl)

define new colours (search_color_1..n)
define functions <select_search_color_1>..n
    or parameterise.  HOW?
    use commands:  `quickhl add pattern` (delete, reset, toggle)
<show-search-color> -> echo using current colour
<search-color> + reverse function
    or hijack existing functions (better), HOW?
matches are coloured accordingly

# Others

- diff
  - colouring
  - tidying

- markdown
  - colouring
  - abbrev
  - table of contents
  - summarise urls at end of file

- signature
  - colouring
  - hiding

- url
  - colouring
  - ansi escape sequence
  - summarise urls at end of file

- url-abbreviator
  - shorten url in-place
  - use ansi seq for full url
  - summarise urls at end of file

- squeeze
  - squeeze blank lines

- smilies
  - convert text smilies to unicode

