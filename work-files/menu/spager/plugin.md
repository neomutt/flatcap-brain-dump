# Plugins

Plugins may need to register (and possibly unregister)
- functions
- colours
- commands
- config
each needs (domain/uid)

## Pager Config

`set pager_body_plugins = "ansi,diff,markdown,url"`
`set pager_attach_plugins = "ansi,url"`

## Plugins

- tidy headers
  - config `$weed` `$header_color_partial`
  - command `hdr_order`
  - colour `header` `hdrdefault`

- body colours
  - colour `body` `tilde`

- quoted colours
  - colour `quotedN`

- toggle quoted
  - function `<toggle_quoted>`
  - config `$toggle_quoted_show_levels`

- signature
  - colouring
  - hiding
  - colour `signature`

- attachments
  - colour `attachment` `attach_headers`

- ansi colours
  - config `$allow_ansi`

- diff
  - colouring
  - tidying
  - colour `diff_add` `diff_change` `diff_delete` `diff_text`

- markdown
  - colouring
  - abbrev
  - table of contents
  - summarise urls at end of file
  - colour `markdown_h1` `markdown_h2`...

- url
  - colouring
  - ansi escape sequence
  - tidying
    - shorten url in-place
    - use ansi seq for full url
    - summarise urls at end of file

- squeeze
  - squeeze blank lines

- smilies
  - convert text smilies to unicode
    (or vice versa)

## Search Plugin (a la quickhl)

define new colours (search_colour_1..n)
define functions <select_search_colour_1>..n
    or parameterise.  HOW?
    use commands:  `quickhl add pattern` (delete, reset, toggle)
<show-search-colour> -> echo using current colour
<search-colour> + reverse function
    or hijack existing functions (better), HOW?
matches are coloured accordingly

