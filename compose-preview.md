I've had a play with @roccoblues' PR and had a think.
As always, I've gone too far :-)
Some of my ideas are relevant, some more tangential!

Firstly, wow!
It works, it looks good.

### Configuration

set compose_preview      = yes
set compose_show_preview = yes

I think it should be enabled by default.
Enable by default
    most users won't read the release notes

$compose_attach_lines = 7 or 0 for min

pager window displays *pager* view, not mailcap/text view
	option to control this?
	OR pager for first attach (main message)
	and mailcap for the rest

### Layout

need better sharing of space
    limit Attach to how many rows?
    or msg has min rows?

advanced: 
    making the whole screen a view (meaning that <page-down> would scroll the
    envelope part off the top), would be trickier

insert pager window below attachment menu
	only if there's >5 lines, say
		e.g. huge list of attachments
	OR, limit attachment list to 5 or 10 lines, like $pager_index_lines
		use rest for the pager

### Status Bars / Feedback

text postition need feedback => need total size (rows)
    45%

"Attachments" simple bar => formatted bar
    'n' attachments, remove from compose bar?

Preview Bar from Simple to Formatted?
    or put %age in Attachment bar on r.h.s.

change attachment bar to show the number of attachments

$compose_attach_status_format!?

### Functions / Bindings

bindings

fn to toggle preview, cf sidebar

| Function                    | Opcode                       |
| :-------------------------- | :--------------------------- |
| `<preview-page-up>`         | `OP_PREVIEW_PAGE_UP`         |
| `<preview-page-down>`       | `OP_PREVIEW_PAGE_DOWN`       |
| `<preview-half-up>`         | `OP_PREVIEW_HALF_UP`         |
| `<preview-half-down>`       | `OP_PREVIEW_HALF_DOWN`       |
| `<preview-line-up>`         | `OP_PREVIEW_LINE_UP`         |
| `<preview-line-down>`       | `OP_PREVIEW_LINE_DOWN`       |
| `<preview-top>`             | `OP_PREVIEW_TOP`             |
| `<preview-bottom>`          | `OP_PREVIEW_BOTTOM`          |
| `<preview-search>`          | `OP_PREVIEW_SEARCH`          |
| `<preview-search-next>`     | `OP_PREVIEW_SEARCH_NEXT`     |
| `<preview-search-opposite>` | `OP_PREVIEW_SEARCH_OPPOSITE` |
| `<preview-search-toggle>`   | `OP_PREVIEW_SEARCH_TOGGLE`   |

reusing pager's bindings would make attachment list unreachable

preview binding => menu bindings and links / priority / focus?

OP_PREVIEW_XYZ if not bound transformed into OP_XYZ
    HOW?
    OP_PREVIEW_XYZ = OP_XYZ + 1000?
    likewise sidebar

### Colours

colour observer
    color normal, etc

colour for preview window?
    and/or envelope
    config to hide preview simple bar?

color body, signature, etc
    apply to preview?
    need search colour if <search> is used

### Events / Notifications

colour
window
editing msg (can affect anything)

### Problems

attachments take up one more row than they need

attachments - fix view
    after adding attachments, the window is the right size,
    but only the last is visible

Page Up / Down min 1 row!
    use (Page Size - 1) min overlap

### Testing

tests

- plain text
- unicode text
- embedded ansi escape sequences
- ^H overtype sequences
- emojis
- text wrapping
- urls

