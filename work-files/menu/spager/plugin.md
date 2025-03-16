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

## Plugin Usage by Dialog

- Email Pager
  - Manipulate Text
    - ansi                .       body    attach
    - diff                .       body    attach
    - markdown            .       body    attach
    - smilies             .       body    attach
  - Colour Text
    - attachment colour   .       .       attach
    - body colours        .       body    .
    - quoted colours      .       body    .
    - signature colour    .       body    .
    - url colour          .       body    .
  - Hide/Show Text
    - squeeze             .       body    attach
    - tidy headers        header  .       .
    - toggle quoted       .       body    .
  - Special
    - search colour       .       body    .
    - url link            header  body    attach

- Compose
  - Manipulate Text
    - ansi                .       body    attach
    - diff                .       body    attach
    - markdown            .       body    attach
    - smilies             .       body    attach
  - Colour Text
    - attachment colour   .       .       attach
    - body colours        .       body    .
    - quoted colours      .       body    .
    - signature colour    .       body    .
  - Hide/Show Text
    - squeeze             .       body    attach
  - Special
    - search colour       .       body    .
    - url                 .       body    attach

- View Attachments
  - Manipulate Text
    - ansi                .       body    attach
    - diff                .       body    attach
    - markdown            .       body    attach
    - smilies             .       body    attach
  - Hide/Show Text
    - squeeze             .       body    attach
  - Special
    - search colour       .       body    .
    - url                 .       body    attach

- Help Page
  - ansi

- Info Pages
  - ansi

- Log Messages
  - log colours


## Plugin Details

- ansi
  - config `$allow_ansi`

- attachment colour
  - colour `attachment` `attach_headers`

- body colours
  - colour `body` `tilde`

- diff
  - colouring
  - tidying
  - colour `diff_add` `diff_change` `diff_delete` `diff_text`

- log colours
  - colouring

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

