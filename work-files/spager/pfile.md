# Paged File Cache

add_text(abc), raw(RED), text(def), raw(END), text(ghi)
File    "abcREDdefENDghi"
Cache   "abc_def_ghi"

Segments    (1-3), (7-9), (13-15)   file offsets
            (1-3), (4-6), (7-9)     cache offsets

# PFile
    File -> /tmp/...
    cache 64KiB
    temp AttrColor

# PRow
    file offset

# Segments
    relative to Row
    Segments need to cover *every* char

get_cache() -> "abcdefghi"  from cache or file
    extract text for screen
    Segments give attrs/colours     AttrColor
    merge with search

------------------------------------------------------------

# Segment Layers

If Layer is NULL (no effect), it should use minimal memory/Segments
so transfer of data is quick

Layers *could* alter colour/attrs or default

PFile       raw text
L0 PRow     Segment1..m     assemble/colour parts of raw text
L1 PRow     Segment1..n     assemble/colour parts of previous Layer
L2 PRow     Segment1..p     assemble/colour parts of previous Layer

L2 does L1.get_row(); apply Segment2
L1.get_row() does L0.get_row(); apply Segment1
L0.get_row() does read_file / get cache

Changing *any* Layer => rebuild all Layers

------------------------------------------------------------

# Email Pager

Multiple headers spread over many Rows

Header1 xyz abc pqr\n
--> jkl vwx def

File contains raw text
Cache contains single Row version
*newlines*/tabs/leading stripped

Caller can mess with the order / visibility
Pager does normal wrapping -- acceptable?
    maybe not

If we strip \n and <tab>, then we'll need to introduce a " " (space)
Parsing a diff, we might want/need to replace @@.* with styled text
=> Segment might hold custom text
=> get_cache() needs to assemble Segments (some cached, some in Segment)

What does search match against?
    *Has* to be **visible** text
Cache needs to be fixed text -- can't let plugins change it.
OR regenerate cache after plugin as run (multiple plugins)
    => get_cache() is simple, so is searching (on modded text)

hmm... this is irreversible; we can't generate *clean* text once plugins have run
mods *could* be undone if they used a new *Layer* of Segments
    keep the original cache
    assemble the new Segments on top
    one Layer of Segments per plugin

Enabling/disabling/reordering the plugins =>
    reapply them on top of original Segments
How are multiple Layers of Segments merged/applied?

------------------------------------------------------------

# SPager Updates

Colour: Simple, Regex, Search, etc (+uncolor)
Visibility: hiding/showing Rows, e.g. quoted_context, $weed
Text Modifications by functions/plugins (or sub-Rows text visibility)

## Colour Simple

Changes to AttrColors in-place => repaint
Search - SPager needs to trap this and repaint

## Visibility

Change conceal flag on some Rows and invalidate them
    => recalc, repaint - might cause view to move

## Colour Regex

Can affect many Rows
caller needs to find/reapply
nightmare!
only way - clear all Segments (and coalesce), then
∀ colour reapply ∀ Row, regenerate Segments (then reapply Layers)
Won't affect view

## Text Mods

Start with an empty Layer -- no Rows, no Segments
keep sparse array of PRows - need to be numbered
(ARRAY_BSEARCH()?  binary search)

Markdown "\*\*word\*\*" from previous Layer (+pre, post-text)

PRow(42): Segment1(pre, default); Segment2("word", bold); Segment3(post, default)

get_row(36) bypasses Layer; get_row(42) matches

generates text from *previous* Layer + *this* Layer's 3 Segments
Layers could change visibility of previous Layers!

Not quite so simple
Each Layer's Segments would be the merged Segments ∀ previous Layers

------------------------------------------------------------

# SPager Notes / PFile

Each Layer needs to expose the number of Rows it has
    => allows Layer to add/remove Rows
    => markdown could summarise links at the bottom of the page
    => text/markdown could insert Table of Contents
Complex markdown replace link inline [text](url) -> _text_

# URL Overlay

Markup can occur in any Layer
Segment(s) need attribute flag that's preserved across merge
Segment needs prefix, suffix strings (ANSI escape sequences)
Splitting a Segment duplicates prefix/suffix, preserves attr
PFile must allocate UIDs for each new url
Splitting Segment preserves UID across parts
If a single char in a single Segment exists with URL attr, then apply

## recalc()

=> gen Results Layer
is this distinct from the Search Segments?
prob separate, search could change often
expensive to recalc Layers (how expensive?)

NOTE: url overlay breaks if window moves
    If window moves, but doesn't change, e.g. toggle sidebar_on_right,
    then in a perfect world recalc() doesn't get called, just repaint().
    Moving the window will mess up the absolute coords needed for the url.

## repaint()

∀ Row, ResultLayer.get_text() -> plain text
∀ Segment (merge Search) render text to screen
If Segment is URL, push Segment to UrlPaint[]
    need absolute Window Coords too
    Segment contains (prefix, suffix, AttrColor, offset into Row, num bytes)
    need to store **window-relative** coords PLUS window ptr in UrlPaint[]
        so that moving the window doesn't cause problems
∀ UrlPaint
    move cursor
    gen ANSI
        (colour, attr, url)
        (end, end url)
    write ansi1
    write text
    write ansi2
    restore cursor

At Markup time, apply MT_COLOR_URL too
    (can be overridden by Layers)

when wrapping a URL, disable $marker for that line

------------------------------------------------------------

Row Flag to affect wrapping?
    [default, none, force marker, use tab, no marker]

Multi-Layer - which are wrapped?
    When are they wrapped?
    Just Result?  recalc()?

Do plugins apply to mailcap-rendered attachments?

------------------------------------------------------------

# Caching

PFile, PLayer, PRow
    Layers need to know parents, ask PFile

Caller generates text
    pf = create_pfile()
    pl = create_layer(pf, true)         enable cache
    pr = create_row(pl)

∀ chunk, add_text|colored|raw(pr, chunk)
    -> file
    -> cache

PLayer owns cache
    passes all chunks to PFile
    or keep Layers simple, put cache in file
        NO doesn't work
    **which** Layer is magic and knows to ask for the cache?
    same for backing file

PFile   pf_get_row(n) -> search L3 -> L1
PLayer1 -> cache/file   Rows 1-10
PLayer2 -> cache        Rows 6-8
PLayer3 -> cache        Rows 1-7

PRow -> get_cache(Layer, x, y) -> text

------------------------------------------------------------

# Caching 2

create_layer(pf, true)  -> L1(cache, file)
create_layer(pf, false) -> L2(-, -)

add_text(L1)    -> text -> cache, text -> file
add_text(L1)    -> ? no Layers only manipulate text
    => cache/file are in PFile
       add_text() ops on PFile

Layers create mods upon **file**, or **Layers**
    does PFile have Layer?
**What** does a Layer work upon?  Markup

Segments act upon Rows (containing Markup)

------------------------------------------------------------

File
    abc \n RED def END \n ghi \n        embedded ansi
    012  3 456 789 10  13 14  17        plain text

Row 1   offset  0   4 bytes     }
    2   offset  4   10 bytes    } offsets into file
    3   offset  14  4 bytes     } get_text(Row) -> cached string

**Row** owns file, cache

Can generate file/cache, but can't gen cache from file

Markup includes plain text (for Layer 1)

Row 1   Markup  (0,3,plain)     } don't include line endings
    2   Markup  (3,3,RED)       } offsets into raw text
    3   Markup  (0,3,plain)     } get_text(Row), gen_string from (raw+markup)
                                insert clean \n line endings

------------------------------------------------------------

Layer: num_rows, Row[]
    Layer 1 complete, others can be sparse?

Search owned by Row - needs(first,last), (color, merged_color)
    => can't do multi-line searches
Test regexes "abc$\n^def" -- WORKS

Search acts on text resulting of Layer merging => search is in PFile
PFile holds Markup[] search_matches!
    NO need Row pointer too

------------------------------------------------------------

# Searching

Multiple Layers, many Rows, only search visible Rows
How do we search for <tab> if whitespace is transformed?
Is <tab> preserved through Layers?  just *rendered* wide, later?
We want to search entire file, but rendered file could be huge
Use rolling window, asking PFile for Rows of text
Need to remember Row num, offset into Row, length
What if match spans multiple Rows?
How greedy is "."?  -- VERY. it matches \n
    Test `.` against `\n` and `.*` against entire file!
Start basic: Search => ∀ get_row(n), regex match
    => ARRAY search_matches: use Markup struct for simplicity
    NO, need Row num in each search match
    OR add Row num to Markup
Needs to be easy to apply over TextMarkup
Rendering a Row {MarkupArray}, get_text(Row)
Scan SearchArray for matching Row num (could be multiple)
Does searching extend into attachments?  probably

------------------------------------------------------------

# Layers / Rows

Layer 1 contains Rows 1-10          Array: Row1..10
Layer 2 deletes even Rows           Array: Row1,3,5,7,9
Layer 3 inserts 2 Rows              Array: Row1,3,5,N,M,7,9

Layers want to be independent of each other => no pointers?
    NO.  Need pointers or there's too much duplication
    => ARRAY of `Row *`
    => don't need Row numbers (each Layer is complete)

Layer2: dup_layer(L1); manipulate

Could use Layers for weeding / hdr_order
When freeing Layer, need to know which Rows are ours?
    => ref count Rows
    => dup_layer() incs ref-count

Need to be careful when manipulating Rows, copy first
PFile.get_row(n) only needs to look at last Layer
    get_num_rows() same

Each Row needs to know its parent / originator Layer to get the cache
Row: get_text() -> whoever owns Row shouldn't affect behaviour
Row holds: raw offset, cache offset, bytes, markup
    Layer holds file, cache

Row.get_text(Row)
    if cache_offset is in cache, return pointer into cache
    else read file from raw_offset, bytes, then   NO

Who translates raw file into cached file (that Markup uses)?
Layer needs to remember add_text() vs add_raw()
Other Layers may just cache useful text, e.g. subtle rewrites

------------------------------------------------------------

# Layer Translation

File contains raw text
Cache contains filtered text

Do we need the distinction?
Can't the Layer do that modification?

File    xyzREDabcENDpqr
Cache   xyzabcpqr       This is **useful**; want big cache of searchable text

Layer1
    File    xyzRED...
    Cache   xyzRED
Layer2
    File    -
    Cache   xyzabc

Do we end up with a 64KiB cache per Layer?
OR Layer1 has file, LayerN has cache?
(multiple Layers could have caches for sundry text)

What's the min we need for hiding raw ansi?

Layer1: Name "RAW"
Layer1, Row1 Markup (xyz, none), (abc, RED), (pqr, none)
    Row offsets are into *raw* file
    get_text() uses cache of 64 KiB of raw file
    then assembles text using Markup.  NO
    Markup offsets don't match result of get_text()
    get_text() returns raw text file, which can be rendered

Layer2: Name: "CLEAN"
Layer2, Row1: markup, same but with offsets into its *clean* text
    controls 64 KiB cache of clean text
    markup offsets are into the clean text
    get_text() returns a pointer into the clean text
    "cleaning" unifies Unicode whitespace, line endings
        strips ansi, strips manpage backspaces

------------------------------------------------------------

# Layer Translation 2

Generating L2 benefits from L1 having a cache
Keep a cache per Layer which generating
only keep last Layer's cache?
raw text won't change, but other Layers may introduce
    config/configurable colours, functions, commands
changes could affect Layer and lower Layers!
plugins should scan text to see if they're needed, or NULL
Does each plugin **need** a separate Layer?  maybe not
What does each plugin **do**?
    diff mostly colours
    markdown edits

## Weeding

Layer "weeding" / hdr_order

Raw text: H1, H2, H3, ... H99
Lots of wrapping, some space, some tabs
weeding needs to happen before other "cleaning"
it unifies by unwrapping, reordering, hiding
Rows have a HEADER colour + markup for other header colours
Is unwrapping wanted?  or just insert uniform <tab>?
flag Row as "don't wrap"?
    preserve header formatting?

Each Layer is only caching the Rows it changes!
    so weeding is only headers
    markdown is only body

Caller creates PFile, PLayer, and adds PRows
When done, we can apply Layers on top for styling

------------------------------------------------------------

# Email Pager 2

Raw email must be decoded first, else first Layer is unusable
What does caller do as it's writing the file?

Header, Body, Attachment(s), [-- markers --]

Who tidies/unifies the headers?
    initial caller?
    Layer?

if **any** tidying is toggleable, then a Layer handles it

original file is immutable
Body Layers: diff, markdown, signature
Attach Layers: prob same

Are Email components separate files, separate Layers?
    Any advantage?
    Yes for attachments and/or mailcap rendering
    Attachments are likely encoded.
    Decode to separate files
Layer1: Header, Body
Layer ∀ attachment: File -> raw file?
    or mailcap'd file

How do diff/markdown Layers work on them?
    sub-Layers?!

Just use external colouriser and interpret ansi (Layer)
    does $allow_ansi affect attachment rendering?
        YES
    toggle_quoted, toggle_quoted_show_levels
        find and mark some Rows as **Conceal**
    ideally it'd be a separate Layer
    in case some other Layer was also doing concealing

LayerN gets raw from Layer N-1
Layer1 gets raw from FILE

------------------------------------------------------------

(Neo)Mutt how many fillbuf() file reads are required
    for one <scroll-down> action?
    ANS: 1 for each line
    worse still, the refresh is happening every timeout (1 sec)
    (regardless of $timeout)

Only write file if cache is full!
    => raw text cache

<save> can dump raw cache

ansi layer doesn't need much storage
nor markdown layer
    cache bold, end, etc sequences just once

------------------------------------------------------------

Layers
    raw text
    clean (ansi free)
    tidy headers
    do markdown
    hide signature
    toggle quoted
    attachments * n
    search

This order implies that
    markdown doesn't apply to attachments,
    but search does

needs to come later?
what about ansi?
    for colorisers of attachments

apply ansi twice?
does allow_ansi apply to attachments
    yes, atm

layers don't need a pointer to a parent *layer*
they need a parent *cache* pointer
    => PFile has a cache (file, cache)

layer_ansi(LayerN) -> new layer
    or LayerN of NULL

search layer functions => search_layer_function_dispatcher()
no search matches => NULL layer

------------------------------------------------------------

merge (cache & file)
cache size set by layer
cache overflow => write entire file

many layers will need very little caching
    let alone a file

one layer per attach
    cache or don't cache?
    file (raw)
    cache is mailcap'd text

------------------------------------------------------------

# Email Pager 3

When generating the file, which lines should the caller markup?

Distinguish:
- header        MT_COLOR_HDRDEFAULT
- body          MT_COLOR_BODY
- attachments   MT_COLOR_ATTACHMENT

Leave everything else to plugins

What about header visibility / order (weed/hdr_order)?

To avoid rewriting the file, we want to dump all the headers,
then *conceal* the ones we don't want.

Which colours should apply to attachments?
- body?
- quotedN?
- signature?
currently these all do!

Need special wrapping for attachment markers
    [-- xyz --]
don't use $wrap, only wrap at screen width (or perhaps never wrap (they're special))

how does "$display_filter" fit in with layers, etc?

