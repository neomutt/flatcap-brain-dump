## Colouring

Currently, the colours are magic control codes that are inserted into the text.
The Expando code needs to recognise them and ignore them when calculating widths.

Only Expando Nodes are coloured and only `$index_format`s `%s` requires two colours.
If `%s` is split into two pieces, then colouring can be done more easily.

If the render function can return three strings, the expando code can make smarter decisions.

- Render `%X` -\> `[colour]` + `John Smith` + `[end-colour]`

The prefix/suffix parts can be considered zero-width.
The text can be truncated if it needs to be, leading to:

- `[colour]` + `John Sm` + `[end-colour]`

