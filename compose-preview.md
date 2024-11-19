I've had a play with @roccoblues' PR and had a think.
As always, I've gone too far :-)
Some of my ideas are relevant, some more tangential!

Firstly, wow!
It works, it looks good.

## Configuration

Either:
- `set compose_preview      = yes`
- `set compose_show_preview = yes`

I think it should be enabled by default.
Most users won't read the release notes and never hear about our new features.

Do we want to support any Pager config?

- `$allow_ansi` -- Allow ANSI color codes in rich text messages
- `$markers` -- Display a '+' at the beginning of wrapped lines in the pager
- `$pager_context` -- Number of lines of overlap when changing pages in the pager
- `$smart_wrap` -- Wrap text at word boundaries
- `$tilde` -- Display '~' in the pager after the end of the email
- `$wrap` -- Width to wrap text in the pager

## Layout

Few users will have an 80x24 Terminal.
Whatever the size of Terminal, however many Attachments they have,
the default layout of Envelope, Preview and Attachments should be pleasing.

If there's enough space, neither the Preview nor the Attachments should be limited.

Otherwise, we probably want to set a maximum number of Attachments, or a minimum number of Preview rows.

- `"$compose_preview_min_rows"`
- `"$compose_attach_max_rows"`

If the Terminal is very short, perhaps we could hide the Preview, or just let the Attachments get clipped.

We should probably think of some way to test the possible layouts.

**Advanced Idea**

Make Page-Up/Down act on the entire Dialog.

The Dialog would comprise: Envelope, Preview, Attachments.
Each would use as many rows as they needed, possibly more rows than the screen had.
Page-Up/Down would move the set of { Envelope, Preview, Attachments } up and down.
(I have no idea how to implement this :-)

## Status Bars / Feedback

If the Preview displays a long email, it would be good to show some feedback on the position, e.g. "15%"

We could add this to the Compose Bar, but it's a bit far away from the Preview.
It might be better to upgrade the "Attachments" Simple Bar to a formatted Bar.
e.g. `|3 Attachments                  25%|`

This would require us to measure the email text (or count the lines).

We've already got `$compose_format` and use `$attach_format`.
It would probably have to be the unwieldy: `$compose_attach_status_format`

**Advanced Idea**

Create a Scrollbar Window.
This would be 1 character wide Window placed to the right of the Preview (or the Pager, etc).
This would be a simple, passive, Window listening to Notifications from the Preview.

## Functions / Bindings

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

**Advanced Idea**

NeoMutt supports an idea of a 'focussed' Window.

This would allow us to reuse a basic function like `<page-up>`,
whose behaviour would be determined by the Window it acted in.
Set Focus to the Attachment Window, `<page-up>` affects the Attachments.

## Colours

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

## Events / Notifications

The Preview Window can be affected by the following Notifications:

- Colour `MT_COLOR_NORMAL`
- Window
  - `NT_WINDOW_STATE` (visibility, resized)
  - `NT_WINDOW_DELETE` (shutdown)
- Email `NT_EMAIL` (edited)

**Note**: Editing the message can affect everything:

- The message itself
- Attachments, by the `attach:` keyword
- Security, by the `pgp:` keyword

## Problems

- Attachments take up one more row than they need
  (There's always a blank line)

- Only the last Attachments is visible
  After adding lots of Attachments, the window is the right size, but only the last Attachments is visible.
  `<previous-entry>`, `<next-entry>` fixes the view.

- Page Up / Down need a minimum of 1 row!
  If there are **lots** of Attachments, the Preview Window becomes small.
  Page Up / Down stop working.
  They should probably move `(Page Size - 1)` rows (giving a 1 line overlap)

## Testing

Test behaviour of:

- Plain text
- Unicode text
- Embedded ANSI escape sequences
- ^H overtype sequences
- Emojis
- Text wrapping
- URLs

