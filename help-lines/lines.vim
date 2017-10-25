syn clear
syn match Oddlines  "^.*$" contains=ALL nextgroup=Evenlines skipnl
syn match Evenlines "^.*$" contains=ALL nextgroup=Oddlines  skipnl

hi Oddlines  guifg=NONE guibg=NONE
hi Evenlines cterm=underline guifg=NONE guibg=NONE
