" set syn=gitlog

syntax match git_hash "\%3v\x\{7,8\}"
syntax match git_date "(\d\+ [^)]\+)"
syntax match git_tag  "([^0-9#][^)]\+)"
syntax match git_user "[^(]\+$"

highlight git_hash ctermfg=red
highlight git_date ctermfg=green
highlight git_tag  ctermfg=yellow
highlight git_user ctermfg=grey

