
" Vim syntax for NeoMutt color commands based on the given EBNF

" Use very magic mode for simpler regex
syntax match NeoMuttColorCommand /\v^color\s+(\S+)/
syntax match NeoMuttSimpleObject /\v\<(attachment|bold|compose_header|compose_security_both|compose_security_encrypt|compose_security_none|compose_security_sign|error|hdrdefault|indicator|italic|markers|message|normal|options|progress|prompt|quoted0|quoted1|quoted2|quoted3|quoted4|quoted5|quoted6|quoted7|quoted8|quoted9|search|sidebar_background|sidebar_divider|sidebar_flagged|sidebar_highlight|sidebar_indicator|sidebar_new|sidebar_ordinary|sidebar_spool_file|sidebar_unread|signature|stripe_even|stripe_odd|tilde|tree|underline|warning)\>/
syntax match NeoMuttPatternObject /\v\<(index|index_author|index_collapsed|index_date|index_flags|index_label|index_number|index_size|index_subject|index_tag|index_tags)\>/
syntax match NeoMuttRegexObject /\v\<(attach_headers|body|header)\>/
syntax match NeoMuttRegexBackrefObject /\v\<status\>/

" Color descriptions
syntax match NeoMuttColorDescription /\v\<(default|(alert|bright|light)?(black|red|green|yellow|blue|magenta|cyan|white)|color\d{1,3}|#([0-9A-Fa-f]{6}))\>/

" Attributes
syntax match NeoMuttAttribute /\v\<(blink|bold|italic|none|normal|reverse|standout|underline)\>/

" Numbers 0-255
syntax match NeoMuttNumber0to255 /\v(25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)/

