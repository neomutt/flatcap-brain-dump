Subject: The Trouble with the Docs

## Introduction

A user's reading the NeoMutt guide on our website.
They spot a mistake in, say, $compose_format.

They helpfully decide to try to fix the problem, so they:
- Create a Pull-Request for the website -- WRONG
- They find the DocBook source in the code repo -- WRONG, it's not there
- Are told that they need to edit `mutt_config.c` -- Source code!

This isn't good enough.

A while back I created a diagram[1] to show the complexity of generating the
documentation.  Add to that the manual steps and evil build script[2] required
to split up the guide for viewing on the website.

[1] https://neomutt.org/images/make-docs.png
[2] https://github.com/neomutt/docbook/blob/master/build

It's too much work (and can't be automated)
Few people understand it.
The effort required to update the docs discourages people.

## Goals

* Guide Re-write

NeoMutt's Guide covers everything, somewhere.  The trouble is finding what you
need.  The Guide needs some serious editing.  It needs splitting into
task-oriented sections.

* Availability

There are three places a user should be able to read the NeoMutt Guide:

- Website : integrated and themed
- Locally : Local files installed with NeoMutt (text or html)
- NeoMutt : Context-sensitive help within the program

* Updatability

If the reader finds a mistake, or would like to offer some improvements, then
it should be immediately obvious how they would do that.

- Website : "Improve this page" button on every page
- Local files : Introduction gives email of Users mailing list
- NeoMutt : "Improve this page" function (emails User mailing list)

## Solution?

* Convert Guide to markdown

Initially, this will just be a few very large markdown files.
Later, editing will split them up.

* Strip `mutt_config.c` of comments

They're non-functional

--------------------------------------------------------------------------------

The are lots of sources for NeoMutt's documentation:
    DocBook xml files
    Text files (and markdown)
    Manual pages
    Comments in the code (mutt_config.c)

