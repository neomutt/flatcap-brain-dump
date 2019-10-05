
**simple-object** -- attachment bold error hdrdefault indicator markers message normal options progress prompt search signature tilde tree underline warning
- `color simple-object [ attribute... ] foreground background`
- `uncolor simple-object`

**simple-index** -- index_collapsed index_date index_label index_number index_size index_tags
- `color simple-index [ attribute... ] foreground background`
- `uncolor simple-index`

**simple-sidebar** -- sidebar_divider sidebar_flagged sidebar_highlight sidebar_indicator sidebar_new sidebar_ordinary sidebar_spoolfile
- `color simple-sidebar [ attribute... ] foreground background`
- `uncolor simple-sidebar`

**simple-compose** -- header security_encrypt security_sign security_both security_none
- `color compose simple-compose [ attribute... ] foreground background`
- `uncolor compose simple-compose`

--------------------------------------------------------------------------------

**quoted-object** -- quoted quoted1 quoted2 quoted3 quoted4 quoted5 quoted6 quoted7 quoted8
- `color quoted-object [ attribute... ] foreground background`
- `uncolor quoted-object`

--------------------------------------------------------------------------------

**regex-list** -- attach_headers body header
- `color regex-list [ attribute... ] foreground background regex`
- `uncolor regex-list regex`
- `uncolor regex-list *`

--------------------------------------------------------------------------------

**status-list**
- `color status [ attribute... ] foreground background [ regex [ num ] ]`
- `uncolor status regex`
- `uncolor status *`

--------------------------------------------------------------------------------

**index-list** -- index index_author index_flags index_subject index_tag
- `color index-list [ attribute... ] foreground background pattern`
- `uncolor index-list pattern`
- `uncolor index-list *`

--------------------------------------------------------------------------------

**everything**
- `uncolor *`

