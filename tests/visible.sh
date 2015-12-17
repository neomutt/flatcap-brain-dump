#!/bin/bash

MUTTRC="test.rc"

function run_mutt()
{
	local config="$1"

	./mutt -n -F $config
}

function base_config()
{
	cat <<-EOF
		unset help
		set status_on_top

		set spoolfile =  "~/Mail/inbox"

		set sidebar_format = "%B"

		bind index,pager \CP sidebar-prev
		bind index,pager \CN sidebar-next
		bind index,pager \CO sidebar-open
		bind index,pager B   sidebar-toggle-visible

		set folder="~/Mail"
		mailboxes "+fruit.0.apple"
		mailboxes "+fruit.0.banana"
		mailboxes "+fruit.0.cherry"
		mailboxes "+fruit.0.damson"
		mailboxes "+fruit.0.elder"
		mailboxes "+fruit.0.fig"
		mailboxes "+fruit.0.haw"
		mailboxes "+fruit.0.ilama"
		mailboxes "+fruit.0.jackfruit"
		mailboxes "+fruit.0.kumquat"
		mailboxes "+fruit.0.lemon"
	EOF
}

function test_startup()
{
	local sidebar
	local width

	for sidebar in yes no; do
		for width in 0 40; do
			(
				base_config
				cat <<-EOF
					set sidebar_visible=$sidebar
					set sidebar_width=$width
					set status_format = "Test: startup -- visible=$sidebar, width=$width"
				EOF
			) > $MUTTRC

			run_mutt $MUTTRC
		done
	done
}

function test_transition_no_change()
{
	(
		base_config
		cat <<-EOF
			set status_format="test1.1 No change -- START: visible,20 -- SET: visible,20 -- RESULT: visible,20"
			set sidebar_visible=yes sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test1.2 No change -- START: hidden,0 -- SET: hidden,0 -- RESULT: hidden,20"
			set sidebar_visible=no sidebar_width=0
			macro index,pager <F1> "<enter-command>set sidebar_visible=no sidebar_width=0<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=no sidebar_width=0<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC
}

function test_transition_set_width()
{
	(
		base_config
		cat <<-EOF
			set status_format="test2.1 Set Width -- START: hidden,20 -- SET: hidden,40 -- RESULT hidden,40"
			set sidebar_visible=no sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=no sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_width=40<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test2.2 Set Width -- START: visible,20 -- SET: 0 -- RESULT: hidden,20"
			set sidebar_visible=yes sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_width=0<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test2.3 Set Width -- START: visible,20 -- SET: 40 -- RESULT visible,40"
			set sidebar_visible=yes sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_width=40<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC
}

function test_transition_set_visible()
{
	(
		base_config
		cat <<-EOF
			set status_format="test3.1 Set Visible -- START: hidden,20 -- SET: visible -- RESULT visible,20"
			set sidebar_visible=no sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=no sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=yes<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test3.2 Set Visible -- START: visible,20 -- SET: hidden -- RESULT hidden,20"
			set sidebar_visible=yes sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=no<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC
}

function test_transition_set_both()
{
	(
		base_config
		cat <<-EOF
			set status_format="test4.1 Set Both -- START: hidden,20 -- SET: visible,0 -- RESULT visible,20"
			set sidebar_visible=no sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=no sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=yes sidebar_width=0<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test4.2 Set Both -- START: hidden,20 -- SET: visible,40 -- RESULT visible,40"
			set sidebar_visible=no sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=no sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=yes sidebar_width=40<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test4.3 Set Both -- START: visible,20 -- SET: hidden,0 -- RESULT hidden,20"
			set sidebar_visible=yes sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=no sidebar_width=0<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

	(
		base_config
		cat <<-EOF
			set status_format="test4.4 Set Both -- START: visible,20 -- SET: hidden,40 -- RESULT hidden,40"
			set sidebar_visible=yes sidebar_width=20
			macro index,pager <F1> "<enter-command>set sidebar_visible=yes sidebar_width=20<enter>"
			macro index,pager <F2> "<enter-command>set sidebar_visible=no sidebar_width=40<enter>"
		EOF
	) > $MUTTRC

	run_mutt $MUTTRC

}


test_startup
test_transition_no_change
test_transition_set_width
test_transition_set_visible
test_transition_set_both
