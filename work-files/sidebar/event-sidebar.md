#### Data/View Changes

| Data/View Change    | Affects        | Result
| :------------------ | :------------- | :------------
| Account new         | Displayed text | :gear: recalc
| Account change      | Displayed text | :gear: recalc
| Account deleted     | Displayed text | :gear: recalc
| AccountView changed | Displayed text | :gear: recalc
| Mailbox new         | Displayed text | :gear: recalc
| Mailbox changed     | Displayed text | :gear: recalc
| Mailbox deleted     | Displayed text | :gear: recalc
| MailboxView changed | Displayed text | :gear: recalc

#### Config Changes

| Config Change                  | Affects           | Result                    | Notes
| :----------------------------- | :---------------- | :------------------------ | :--------------------------------
| ascii_chars                    | Divider           | :paintbrush: repaint      | Unless character changes width
| folder                         | Displayed text    | :gear: recalc
| sidebar_component_depth        | Displayed text    | :gear: recalc
| sidebar_delim_chars            | Displayed text    | :gear: recalc
| sidebar_divider_char           | Dividing line     | :paintbrush: repaint      | Unless character changes width
| sidebar_folder_indent          | Displayed text    | :gear: recalc
| sidebar_format                 | Displayed text    | :gear: recalc
| sidebar_indent_string          | Displayed text    | :gear: recalc
| sidebar_new_mail_only          | Displayed text    | :gear: recalc
| sidebar_next_new_wrap          | Behaviour         | :heavy_check_mark: none
| sidebar_non_empty_mailbox_only | Displayed text    | :gear: recalc
| sidebar_on_right               | Window position   | :paintbrush: repaint      | See: Window position
| sidebar_short_path             | Displayed text    | :gear: recalc
| sidebar_sort_method            | Displayed text    | :gear: recalc
| sidebar_visible                | Window visibility | :left_right_arrow: reflow | See: Window become visible/hidden
| sidebar_width                  | Window size       | :left_right_arrow: reflow | See: Window narrow/widen
| spoolfile                      | Colour of text    | :paintbrush: repaint

#### Colour Changes

| Colour Change     | Affects        | Result
| :---------------- | :------------- | :-------------------
| indicator         | Colour of text | :paintbrush: repaint
| normal            | Colour of text | :paintbrush: repaint
| sidebar_divider   | Colour of text | :paintbrush: repaint
| sidebar_flagged   | Colour of text | :paintbrush: repaint
| sidebar_highlight | Colour of text | :paintbrush: repaint
| sidebar_indicator | Colour of text | :paintbrush: repaint
| sidebar_new       | Colour of text | :paintbrush: repaint
| sidebar_ordinary  | Colour of text | :paintbrush: repaint
| sidebar_spoolfile | Colour of text | :paintbrush: repaint

#### Functions

| Function                       | Change            | Result                    | Notes
| :----------------------------- | :---------------- | :------------------------ | :------------------------------------------------------------
| <sidebar-next-new>           | Move highlight    | :paintbrush: repaint      | Unless highlight moves offscreen, in which case :gear: recalc
| <sidebar-next>               | Move highlight    | :paintbrush: repaint      | Unless highlight moves offscreen, in which case :gear: recalc
| <sidebar-open>               | Open Mailbox      | :gear: recalc             | It's possible that stats will change for the Mailbox
| <sidebar-page-down>          | Move display      | :gear: recalc
| <sidebar-page-up>            | Move display      | :gear: recalc
| <sidebar-prev-new>           | Move highlight    | :paintbrush: repaint      | Unless highlight moves offscreen, in which case :gear: recalc
| <sidebar-prev>               | Move highlight    | :paintbrush: repaint      | Unless highlight moves offscreen, in which case :gear: recalc
| <sidebar-toggle-virtual>     | none              | :heavy_check_mark: none   | Obsolete
| <sidebar-toggle-visible>     | Window visibility | :left_right_arrow: reflow | See: Window become visible/hidden

#### Commands

| Command             | Affects        | Result
| :------------------ | :------------- | :------------
| sidebar_whitelist   | Displayed text | :gear: recalc
| unsidebar_whitelist | Displayed text | :gear: recalc

#### Window Changes

These changes are the effect of other events, e.g. resizing the terminal,
changing config.  In some cases the result will depend on the exact setup of the
screen.  When possible, the Sidebar will **just** be repainted.

| Window Change   | Result                  | Notes
| :-------------- | :---------------------- | :--------------------------------------------------------------------
| Become taller   | :gear: recalc           | Only if there is more text to display, otherwise :paintbrush: repaint
| Become shorter  | :heavy_check_mark: none | Unless highlight is moved offscreen, in which case :gear: recalc
| Become narrower | :gear: recalc           | Affects sidebar_format
| Become wider    | :gear: recalc           | Affects sidebar_format
| Become moved    | :paintbrush: repaint    | If dimensions are the same, otherwise :gear: recalc
| Become visible  | :paintbrush: repaint    | If nothing else has changed, otherwise :gear: recalc
| Become hidden   | :heavy_check_mark: none | Ignore :gear: recalc requests while hidden

