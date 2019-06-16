syntax match notify_bell ":bell:"               conceal cchar=🔔
syntax match notify_code ":wrench:"             conceal cchar=🔧
syntax match notify_docs ":book:"               conceal cchar=📕
syntax match notify_user ":bust_in_silhouette:" conceal cchar=👤

highlight Conceal guifg=white
highlight Folded  guifg=darkgreen

setl conceallevel=2
setl fdt=getline(v:foldstart)
set laststatus=0

iabbrev B :bell:
iabbrev C :gear:
iabbrev D :book:
iabbrev U :bust_in_silhouette:

