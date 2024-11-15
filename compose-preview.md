I've had a play with @roccoblues' PR and had a think.
As always, I've gone too far :-)
Some of my ideas are relevant, some more tangential!

Firstly, wow!
It works, it looks good.
I think it should be enabled by default.

### Configuration


### Layout


### Status Bars


### Bindings


### Colours


### Problems


--------------------------------------------------------------------------------

Compose Preview

set compose_preview      = yes
set compose_show_preview = yes

use `devel_` prefix initially?

Enable by default
    most users won't read the release notes

colour observer
    color normal, etc

attachments take up one more row than they need

attachments - fix view
    after adding attachments, the window is the right size,
    but only the last is visible

text postition need feedback => need total size (rows)
    45%

"Attachments" simple bar => formatted bar
    'n' attachments, remove from compose bar?

need better sharing of space
    limit Attach to how many rows?
    or msg has min rows?

Page Up / Down min 1 row!
    use (Page Size - 1) min overlap

colour for preview window?
    and/or envelope
    config to hide preview simple bar?

Preview Bar from Simple to Formatted?
    or put %age in Attachment bar on r.h.s.

$compose_attach_status_format!?

bindings
    preview_(page|half|line)_(up|down)
    preview_(top|bottom)
    search, search_(next|opposite|toggle)

reusing pager's bindings would make attachment list unreachable

fn to toggle preview, cf sidebar

preview binding => menu bindings and links / priority / focus?

OP_PREVIEW_XYZ if not bound transformed into OP_XYZ
    HOW?
    OP_PREVIEW_XYZ = OP_XYZ + 1000?
    likewise sidebar

editing msg can affect anything

color body, signature, etc
    apply to preview?
    need search colour if <search> is used

$compose_attach_lines = 7 or 0 for min

--------------------------------------------------------------------------------

compose enhancement
	   gzbd | I would like to see the the to,cc,subject etc in the same view along with text/plain attachments.
	flatcap | oh, see what the email _would_ look like?
	flatcap | no, that's not possible (yet! :-)
	   gzbd | IMO this would be a nice visual improvement, since the space is there
	flatcap | yeah, it's a reasonable idea
	      * | flatcap thinks how graphical email programs tend to work
	flatcap | adding a pager in the space at the bottom wouldn't be too hard...
	flatcap | but making the whole screen a view (meaning that <page-down> would scroll the envelope part off the top), would be trickier
change attachment bar to show the number of attachments
insert pager window below attachment menu
	only if there's >5 lines, say
		e.g. huge list of attachments
	OR, limit attachment list to 5 or 10 lines, like $pager_index_lines
		use rest for the pager
	<up>/<down> control attachment selection
	<page-up>/<page-down> control the pager
pager window displays *pager* view, not mailcap/text view
	option to control this?
	OR pager for first attach (main message)
	and mailcap for the rest

