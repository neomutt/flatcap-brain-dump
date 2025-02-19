syntax clear

syntax match green  ".*multipart\/alternative.*"
syntax match cyan   ".*application\/octet-stream.*"
syntax match red    ".*application\/pgp-encrypted.*"
syntax match red    ".*multipart\/encrypted.*"
syntax match yellow ".*text\/plain.*"

highlight green  guifg=#20ff20 guibg=none
highlight cyan   guifg=#20ffff guibg=none
highlight red    guifg=#ff2020 guibg=none
highlight yellow guifg=#ffff20 guibg=none

