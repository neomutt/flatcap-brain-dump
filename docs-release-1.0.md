# Docs Release 1.0

big-doc.md or multi-docs.md

## Sources

muttrc.*
vimrc.*
contrib/*
README*
ChangeLog*
[A-Z]*
po/*
mutt_config.c
functions.h
OPS*
*.[ch] help strings
docs/*
config.h (version)

## Subst

version num - docs
doc dir - muttrc
bindir     } - mutt.1
sysconfdif }

## Destinations

user docs (html)
website (md)
user (txt)

## Sync

code for variables / functions
OPS -> docs, or vice versa?
or manual? NO
embedded help strings
	how to sync?

## Install

base dir /usr or /usr/local
doc/neomutt
man/*/X
install script cp -r
uninstall script rm -fr
copy man pages?
no name clash

## Jobs

sync to source
notify downstreams
regen website
	check links

## Scripts

doc -> website (travis?)
doc -> html
doc -> txt
	(or html -> txt)

## Drop Docs From Source

drop /doc
drop mutt_config.c comments
drop function.h comments

## Contact Distros

talk about packaging

## Future

man pages -> md
script to gen man pages
sample muttrc integrated
ChangeLog/Versions?
howtos
pictures
FAQ
translations
vimrc?
"Edit this page" link

## Restructure

pop
imap
sidebar
caching
credits to end

## Questions

commands used
commit as base
post processing
can we use jekyll to build user html?

