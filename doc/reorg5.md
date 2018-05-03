where do the lists go?
where do we want them to go?

how to link ":help X" to the right page?
sqlite index: Title, metadata, body, links?
ignore common English and markdown -- tool

functions.h, opcodes.h, init.h ->
    reference section
    neomuttrc.5
reference list has negative score so that
    :help X
never goes there unless no alternative
Score for Title, H1, H2, ...

index needs list of every (key)word in neomutt
list of all errors, E123, too
folders
    ref/var
    ref/cmd
    ref/func ... color, error
    intro/xyz
    howto/xyz
    panel/xyz
:help <tab> completion

functions.h, opcodes.h, init.h -> md?
NO LINK?
    seldom changing
    new config -> update: index, section, rc.5

no help index => web search URI?
slash separators for URIs / paths

seldom changing
functions.h - functions
opcodes.h - ops
init.h - cfg
    mutt -D -> csv, json?

functions.h
    "group-reply", OP_GROUP_REPLY, "x" (default key)
OpPager, OpAttach, ... (13)

opcodes.h
    OP_GROUP_REPLY, "desc help" (247)

init.h
    "alias_format", DT_STR, defval, comment (447/-23)

sort (6 sets)
    "alpha", SORT_ALPHA

yml header
    section: intro/panels
    tite
    keywords (equiv to title) for search

intro.md
    website: jekyll -> intro.html
        improve button -> github edit
    help: copy -> /usr/share/doc/neomutt
        improve function -> email edit
    help: cat -> single file?

