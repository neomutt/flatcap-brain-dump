# Pager Plugins

Plugins may need to register (and possibly unregister)
- functions
- colours
- commands
- config
each needs (domain/uid)

## Pager Config

`set pager_body_plugins = "ansi,diff,markdown,url"`
`set pager_attach_plugins = "ansi,url"`

or use "all" for all possible plugins
    which order would they be applied?
    how much does order matter?
    does `set pbp = 'all'` auto-expand to `pbp = 'ansi,diff,...'` ?

## Plugin Usage

- Headers Only
  - tidy headers

- Body Only
  - body colours
  - quoted colours
  - toggle quoted
  - signature

- Body or Attachments
  - ansi colours
  - diff
  - markdown
  - smilies
  - squeeze
  - url

- Attachments Only
  - attachments
  - mailcap

## Plugin Details

- ansi colours
  - config `$allow_ansi`

- attachments
  - colour `attachment` `attach_headers`

- body colours
  - colour `body` `tilde`

- diff
  - colouring
  - tidying
  - colour `diff_add` `diff_change` `diff_delete` `diff_text`

- mailcap
  - transform file into text
  - config `mailcap_path`

- markdown
  - colouring
  - abbrev
  - table of contents
  - summarise urls at end of file
  - colour `markdown_h1` `markdown_h2`...

- quoted colours
  - colour `quotedN`

- signature
  - colouring
  - hiding
  - colour `signature`

- smilies
  - convert text smilies to unicode
    (or vice versa)

- squeeze
  - squeeze blank lines

- tidy headers
  - config `$weed` `$header_color_partial`
  - command `hdr_order`
  - colour `header` `hdrdefault`

- toggle quoted
  - function `<toggle_quoted>`
  - config `$toggle_quoted_show_levels`

- url
  - colouring
  - ansi escape sequence
  - tidying
    - shorten url in-place
    - use ansi seq for full url
    - summarise urls at end of file

## Search Plugin (a la quickhl)

define new colours (search_colour_1..n)
define functions <select_search_colour_1>..n
    or parameterise.  HOW?
    use commands:  `quickhl add pattern` (delete, reset, toggle)
<show-search-colour> -> echo using current colour
<search-colour> + reverse function
    or hijack existing functions (better), HOW?
matches are coloured accordingly

