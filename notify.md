## Key

:wrench: NeoMutt code
:bell: Notification sent
:book: Notes
:bust_in_silhouette: User actions

## Startup

:wrench: NeoMutt created - Object is root of notifications
:book: Start reading config
:bell: **account-post-create** - After Account is created
:bell: **mailbox-post-create** * 3 - After Mailbox is created
:book: The Sidebar would listen to these notifications
:bell: **account-post-create**
:bell: **mailbox-post-create** * 2
:book: All config read
:bell: **startup-complete** - `startup-hook`
:book: No Accounts or Mailboxes are open yet

## Mailbox Open

:book: Main: Open first Mailbox
:bell: **account-pre-open** - `account-hook` - To set Account-connection info
:wrench: Open Account (remote connection)
:bell: **account-post-open** - The Account is open/connected
:bell: **mailbox-pre-open** - `folder-hook` - To set Mailbox-specific config
:wrench: Open Mailbox
:bell: **mailbox-post-open** - Mailbox is open
:bust_in_silhouette: Use Mailbox...

## Mailbox Close

:bust_in_silhouette: Use Mailbox...
:bell: **mailbox-pre-close** - Mailbox is about to close
:wrench: Close Mailbox
:bell: **mailbox-post-close** - Mailbox is closed
:bell: **account-pre-close** - Account is about to close
:wrench: Close Account (remote connection)
:bell: **account-post-close** - Account is closed

## Shutdown

:book: Mailboxes and Accounts are already closed
:bell: **shutdown-starting** - `shutdown-hook`
:bell: **mailbox-pre-delete** * 2 - Before Mailbox is deleted
:bell: **account-pre-delete** - Before Account is deleted
:book: The Sidebar can clean itself up
:bell: **mailbox-pre-delete** * 3
:bell: **account-pre-delete**
:wrench: NeoMutt deleted

## Mailbox Open/Change/Close (same Account)

:book: Main: Open first Mailbox
:bell: **account-pre-open** - `account-hook`
:wrench: Open Account (remote connection)
:bell: **account-post-open** - The Account is open/connected
:bell: **mailbox-pre-open** - `folder-hook`
:wrench: Open Mailbox
:bell: **mailbox-post-open** - Mailbox is open
:bust_in_silhouette: Use Mailbox...
:bell: **mailbox-pre-close** - Mailbox is about to close
:wrench: Close Mailbox
:bell: **mailbox-post-close** - Mailbox is closed
:bell: **mailbox-pre-open** - `folder-hook`
:wrench: Open Mailbox
:bell: **mailbox-post-open** - Mailbox is open
:bust_in_silhouette: Use Mailbox...
:bell: **mailbox-pre-close** - Mailbox is about to close
:wrench: Close Mailbox
:bell: **mailbox-post-close** - Mailbox is closed
:book: If that was the last open Mailbox, close the Account
:bell: **account-pre-close** - Account is about to close
:wrench: Close Account (remote connection)
:bell: **account-post-close** - Account is closed

## Mailbox Open/Change/Close (different Accounts)

:book: Main: Open first Mailbox
:bell: **account-pre-open** - `account-hook`
:wrench: Open Account (remote connection)
:bell: **account-post-open** - The Account is open/connected
:bell: **mailbox-pre-open** - `folder-hook`
:wrench: Open Mailbox
:bell: **mailbox-post-open** - Mailbox is open
:bust_in_silhouette: Use Mailbox...
:bell: **mailbox-pre-close** - Mailbox is about to close
:wrench: Close Mailbox
:bell: **mailbox-post-close** - Mailbox is closed
:bell: **account-pre-close** - Account is about to close
:wrench: Close Account (remote connection)
:bell: **account-post-close** - Account is closed
:bell: **account-pre-open** - `account-hook`
:wrench: Open Account (remote connection)
:bell: **account-post-open** - The Account is open/connected
:bell: **mailbox-pre-open** - `folder-hook`
:wrench: Open Mailbox
:bell: **mailbox-post-open** - Mailbox is open
:bust_in_silhouette: Use Mailbox...
:bell: **mailbox-pre-close** - Mailbox is about to close
:wrench: Close Mailbox
:bell: **mailbox-post-close** - Mailbox is closed
:bell: **account-pre-close** - Account is about to close
:wrench: Close Account (remote connection)
:bell: **account-post-close** - Account is closed

## Notes

Who's sending Notifications?
Who's responding?
Which events need pre/post versions?
Who closes Account?  When?
What do 'open' and 'close' mean for a Mailbox or Account?
  create/delete - Object is created/deleted

Starting points of all events:

assuming nothing's open
mx_mbox_open(M)

M -> [A open -> notify, actual open, (post open?) ]
[m notify, actual open, (post open?) ]

hook.c is listening
  A notify -> A-hook
  M notify -> F-hook

