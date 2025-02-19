syntax match event_recalc  ":gear:"             conceal cchar=⚙
syntax match event_repaint ":paintbrush:"       conceal cchar=🎨
syntax match event_reflow  ":heavy_check_mark:" conceal cchar=✔
syntax match event_reflow  ":left_right_arrow:" conceal cchar=↔️

setl conceallevel=2

hi Conceal guifg=yellow
syn match title "^\C[A-Z][a-z][^:]\+  [^:]\+$"
