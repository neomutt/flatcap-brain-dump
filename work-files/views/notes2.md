# The Actual Index Data

Above, you see who's holding all the data.
Now let's see the important bits:

- `struct MailboxView` - Display data for the Mailbox
  Contains: limit info, threads
- `struct Mailbox` - Folder of emails
  Contains: Emails, paths, message counts
- `struct ThreadsContext` - Threaded tree of Emails
  Contains: threads, hash table of message-ids, sort info
- `struct MuttThread` - Part of an email conversation
  Contains: Email, parent, child
- `struct Email` - An email
  Contains: envelope, body, tags

<img src="https://flatcap.org/mutt/index/index2.svg">

## Opening the Mailbox

First, the user opens a mailbox.

First, the backend creates a `struct Mailbox` and a `struct Email` for each email.
The array `Mailbox.emails` contains pointers to each `Email`.
Its order depends on `$sort`, etc.

In this mailbox, there are 22 emails, 'a' to 'v' and the array has a few empty entries at the end.

## Enabling threading

Next, the user enables threading: `set sort=threads`

The Index creates a `struct ThreadsContext`.
This holds a tree of `struct MuttThread` objects, each of which points to an `Email`.
The layout of the tree depends on the `message-id`s in the emails and config option `$strict_threads`.

This mailbox has two email threads, rooted at 'b' and 'o' and three individual emails, 'a', 'n' and 'v'.

## Limiting to one thread

Next, the user does `<limit-current-thread>` on the 'b' thread.
Then, then collapse one of the sub-threads at email 'd'.

In the `Mailbox`, the array `v2r` ('virtual' to 'real') holds a list of _visible_ emails.
Its order depends on `$sort`, etc.
After the limit, only the green emails are still visible.

## Menu view

The Menu is an abstract view of some data, usually emails.
In the Index, the Menu is backed by the `v2r` array.

In this case, the window for the Menu is only five lines high, so only emails 'd', 'g', 'h', 'i' and 'j' are visible.

Note that the index numbers are the indexes in the `emails` array.
