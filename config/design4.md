New Config Design 4 - Scope

Currently over 400 of the config items are defined in a huge list in mutt_config.c

    { "sidebar_delim_chars",   DT_STR,  R_SIDEBAR, &SidebarDelimChars,        "/." },
    { "sidebar_divider_char",  DT_STR,  R_SIDEBAR, &SidebarDividerChar,       0    },
    { "sidebar_folder_indent", DT_BOOL, R_SIDEBAR, OPT_SIDEBAR_FOLDER_INDENT, 0    },

All the variables are defined in globals.h:

    WHERE char *SidebarDelimChars;
    WHERE char *SidebarDividerChar;
    WHERE char *SidebarFormat;

The booleans are in options.h:

    OPT_SIDEBAR,
    OPT_SIDEBAR_FOLDER_INDENT,
    OPT_SIDEBAR_NEWMAIL_ONLY,

And the Quad-options are in mutt.h:

    OPT_POSTPONE,
    OPT_PRINT,
    OPT_QUIT,

Lots of large global lists.  If/when we move to the new config setup,
I'd like to reduce the scope of a lot of these variables.

For example, the sidebar has 12 user-configurable items:

    OPTSIDEBAR
    OPTSIDEBARFOLDERINDENT
    OPTSIDEBARNEWMAILONLY
    OPTSIDEBARNEXTNEWWRAP
    OPTSIDEBARONRIGHT
    OPTSIDEBARSHORTPATH
    SidebarDelimChars
    SidebarDividerChar
    SidebarFormat
    SidebarIndentString
    SidebarSortMethod
    SidebarWidth

but only three are used outside of sidebar.c

    OPTSIDEBAR
    OPTSIDEBARONRIGHT
    SidebarWidth

I'd like to see the sidebar register its config items and only expose these
three variables as externs.

Component | Config | Used outside Component
----------|--------|------------------------
sidebar   | 12     |  3
notmuch   | 13     |  3
imap      | 15     |  6
nntp      | 23     | 14
hcache    |  5     |  5
pop       |  9     |  2

---

Rich / FlatCap
