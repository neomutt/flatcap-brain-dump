I've had a play with @roccoblues' PR and had a think.
As always, I've gone too far :-)
Some of my ideas are relevant, some more tangential!

Firstly, wow!
It works, it looks good.

### Configuration

Either:
- `set compose_preview      = yes`
- `set compose_show_preview = yes`

I think it should be enabled by default.
Most users won't read the release notes and never hear about our new features.

$compose_attach_lines = 7 or 0 for min

pager window displays *pager* view, not mailcap/text view
	option to control this?
	OR pager for first attach (main message)
	and mailcap for the rest

### Layout

need better sharing of space
    limit Attach to how many rows?
    or msg has min rows?

insert pager window below attachment menu
	only if there's >5 lines, say
		e.g. huge list of attachments
	OR, limit attachment list to 5 or 10 lines, like $pager_index_lines
		use rest for the pager

Advanced Idea: 
    making the whole screen a view (meaning that <page-down> would scroll the
    envelope part off the top), would be trickier

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

Here's a list of all the Functions we _could_ implement.
This would allow the user independent control of the Preview.

We could bind Page-Up/Down by default.

Adding Search Functions would add complexity to the positioning of the text.
(also see Colours, below)

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
| `<preview-toggle>`          | `OP_PREVIEW_TOGGLE`          |

**Advanced Ideas**

NeoMutt supports an idea of a 'focussed' Window.

This would allow us to reuse a basic function like `<page-up>`,
whose behaviour would be determined by the Window it acted in.
Set Focus to the Attachment Window, `<page-up>` affects the Attachments.

### Colours

Currently, Compose only colours the:

- Envelope Headers region, e.g. `Bcc:`
- Security labels, e.g. `Encrypt`

The whole of Compose is also affected by some other colours:

- `normal` - Default colour for all of Neomutt
- `status` - Default colour for Status Bars

This means that the Preview Window needs a colour observer.

One way to save some space, would be to eliminate the Preview Bar
and instead colour the Preview, and/or the entire Envelope region.
A subtle difference in background colour would be enough to make it stand out.

The Preview is monochrome, which makes it nice and simple.
Applying all the layers of colour is what makes the Pager so complicated.

If we implement `<search>` and friends, we'd probably need to support `color search`.
Anything more than that, e.g. `color body`, would need Pager 2.0.

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

