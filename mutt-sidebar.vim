
syn keyword muttrcVarBool	skipwhite contained sidebar_folderindent  nextgroup=muttrcSetBoolAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr
syn keyword muttrcVarBool	skipwhite contained sidebar_newmail_only  nextgroup=muttrcSetBoolAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr
syn keyword muttrcVarBool	skipwhite contained sidebar_next_new_wrap nextgroup=muttrcSetBoolAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr
syn keyword muttrcVarBool	skipwhite contained sidebar_shortpath     nextgroup=muttrcSetBoolAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr
syn keyword muttrcVarBool	skipwhite contained sidebar_visible       nextgroup=muttrcSetBoolAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr

syn keyword muttrcVarNum	skipwhite contained sidebar_refresh nextgroup=muttrcSetNumAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr
syn keyword muttrcVarNum	skipwhite contained sidebar_width   nextgroup=muttrcSetNumAssignment,muttrcVPrefix,muttrcVarBool,muttrcVarQuad,muttrcVarNum,muttrcVarStr

syn keyword muttrcVarStr	contained skipwhite sidebar_delim       nextgroup=muttrcVarEqualsIdxFmt
syn keyword muttrcVarStr	contained skipwhite sidebar_delim_chars nextgroup=muttrcVarEqualsIdxFmt
syn keyword muttrcVarStr	contained skipwhite sidebar_format      nextgroup=muttrcVarEqualsIdxFmt
syn keyword muttrcVarStr	contained skipwhite sidebar_indentstr   nextgroup=muttrcVarEqualsIdxFmt
syn keyword muttrcVarStr	contained skipwhite sidebar_sort        nextgroup=muttrcVarEqualsIdxFmt
syn keyword muttrcVarStr	contained skipwhite sidebar_whitelist   nextgroup=muttrcVarEqualsIdxFmt

syn keyword muttrcCommand	sidebar_whitelist

syn match muttrcFunction	contained "\<sidebar-next-new\>"
syn match muttrcFunction	contained "\<sidebar-next\>"
syn match muttrcFunction	contained "\<sidebar-open\>"
syn match muttrcFunction	contained "\<sidebar-page-down\>"
syn match muttrcFunction	contained "\<sidebar-page-up\>"
syn match muttrcFunction	contained "\<sidebar-prev-new\>"
syn match muttrcFunction	contained "\<sidebar-prev\>"
syn match muttrcFunction	contained "\<sidebar-toggle-visible\>"

syn keyword muttrcColorField	contained sidebar_divider
syn keyword muttrcColorField	contained sidebar_flagged
syn keyword muttrcColorField	contained sidebar_highlight
syn keyword muttrcColorField	contained sidebar_new
syn keyword muttrcColorField	contained sidebar_scrollbar

