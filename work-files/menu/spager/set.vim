syntax match bold    '\v%5v\i+'
syntax match command '\v^set'
syntax match comment '\v^#.*'
syntax match enum    '\v\c<(address|alias|alpha|count|date|date-received|desc|email|flagged|from|keyid|label|name|new|path|score|size|spam|subject|threads|to|trust|unread|unsorted)>'
syntax match enum    '\v\c<(ask-)?(yes|no)>'
syntax match enum    '\v\c<(mbox|mmdf|mh|maildir)>'
syntax match enum    '\v\c<(unset|flat|threads|reverse)>'
syntax match number  '\v-?\d+>'
syntax match string  '\v".*"'

highlight bold    gui=bold
highlight command guifg=#00ffff
highlight comment guifg=#00c000
highlight enum    guifg=#8080ff
highlight number  guifg=#80ff80
highlight string  guifg=#ffff80
