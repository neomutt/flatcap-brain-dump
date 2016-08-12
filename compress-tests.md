# Compress Tests

Open/Close/Append hooks

## (Open) : RO - The folder is just a backup

- Open mailbox - flagged as read-only
- Delete mail - fails
- Append mail - fails
- Change flags - fails
- New mail (externally) - display updated
- Close mailbox

## (Open, Close) : RW - Your compression format doesn't support appending

- Open mailbox - read/write
- Delete mail - succeeds
- Append mail - succeeds
- Change flags - succeeds
- New mail (externally) - display updated
- Close mailbox

## (Open, Close, Append) : RW - Your compression format supports appending

## (Open, Append) : RW - You want to store emails, but never change them


Test broken files:

- bad compression
- bad mailbox inside

------------------------

H hook combinations: Open, Close, Append:
    O
    OC
    OCA
    OA

Actions
    01	open
    02	close
    03	sync (no change)
    04	sync (change)
    05	append one file
    06	delete file
    07	open message
    08	close message
    09	append many files
    10	external mailbox update

Test
    ∀ hook combinations
    ∀ actions

options: delete_on_empty
compressed spool/inbox -- open on startup?
test cli -- "mutt -f mailbox.gz"
all error paths
delete tmp files
delete compress info

bad hooks
    missing %f, %t, both
    bad command
    compressed file contains junk
external AND internal changes -> corrupt
empty files (option save_empty)
    append to empty
    delete last mail

