completion of folders in browser.c

s = save

s   dir
s   dir/
s   file
s   file/
s   new-dir
s   new-dir/
s   path/to/new-dir
s   path/to/new-dir/
s   =path/new-dir
s   =path/new-dir/

relative dir
absolute dir
rel path/to/new (1 part new)
abs /path/to/new
rel new/new/new
abs /new/new/new
=dir (exist)
=new-dir
=path/dir
=path/new-dir

with / without trailing slash

locale: relative, absolute
depth: one, many
trailing: slash, none
abbrev: =, none
new: none, 1, all
dest: file, dir

