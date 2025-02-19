# Index v2 :scroll:

This is a breakdown of how the Index works, what problems it has and what we need to do to fix it.

Everyone's invited to ask questions and make suggestions.
I really need as many people as possible to understand the problem with me.

---

## Introduction

NeoMutt's code has changed a **LOT** since its split from Mutt.
We've refactored to create APIs and libraries to reduce the dependencies and the complexity of the code.
One stubborn area is the Index.

The Index displays a list of `Email`s contained in a `Mailbox`.
The Index can sort this list by `$sort`, etc.
When new mail arrives, the backend, e.g. Maildir, needs to update this list.

Maildir is the worst offender.
It sorts the `Email`s so that when it scans the directories it can work out if any files are new.
If it finds some new files, it creates new `Email`s and adds them to the list.
Then, it tries to restore the Index's sorting order.
If that sounds terrifying, then you're beginning to understand.

The backends can change the order of the `Email` list and the Index has to deal with it.
Not only that, the user doesn't want to see the focus jump around -- sound familiar?

## Data

There are sets of data to consider: mail data and gui data.

We've made some big advances in separating the gui data out of the mail objects, but some still remains.
The plan is that we would have a shadow set of View objects, e.g.

- `Email` - data about the email: headers, etc
- `EmailView` - display data, such as its colour

### Mail Data

The mail data is rooted at the `NeoMutt` object.

`NeoMutt` holds a list of `Account`s, each of which holds a list of `Mailbox`s, which hold a list of `Email`s.

<img width="150" src="https://raw.githubusercontent.com/neomutt/gfx/main/arch/arch-data.svg">

### GUI Data

The gui data is rooted at the `RootWindow` object.

The screen is divided into a nested hierarchy of `MuttWindow`s.
Each window can have some data associated with it.

Here are the windows that make up the Index Dialog:

![index-dialog](https://github.com/neomutt/gfx/raw/main/screenshots/window/dlg-index-pager-sidebar.svg)

This shows the names of the components and some of the data associated with them.

- Index Dialog - `IndexSharedData`
  - Sidebar
  - Container
    - Index Panel - `IndexPrivateData`
      - Index
      - Index Status Bar
    - Pager Panel
      - Pager
      - Pager Status Bar

### Index Shared Data

The `IndexSharedData` is available to all of the associated windows.
For example, the Index has a selected Email in a particular Mailbox in an Account.
The Sidebar uses this information to highlight the current Mailbox.


```c
struct IndexSharedData
{
  struct ConfigSubset *sub;         ///< Config set to use
  struct MailboxView *mailboxview;  ///< Current Mailbox view
  struct Account *account;          ///< Current Account
  struct Mailbox *mailbox;          ///< Current Mailbox
  struct Email *email;              ///< Currently selected Email
  size_t email_seq;                 ///< Sequence number of the current email
  struct Notify *notify;            ///< Notifications: #NotifyIndex, #IndexSharedData
};
```

There is one circumstance where there is more than one Index: attaching an Email from Compose.

This new Index Dialog has its own data and is independent of the original one.
e.g. Applying a limit won't affect the original Index.

### Index Private Data

Much of the data required to work the Index is local to `mutt_index_menu()`.
Some state data is required by other Index functions and that is stored in `IndexPrivateData`.

```c
struct IndexPrivateData
{
  bool tag;                      ///< tag-prefix has been pressed
  int  oldcount;                 ///< Old count of Emails in the Mailbox
  int  newcount;                 ///< New count of Emails in the Mailbox
  bool do_mailbox_notify;        ///< Do we need to notify the user of new mail?
  bool attach_msg;               ///< Are we in "attach message" mode?

  struct IndexSharedData *shared; ///< Shared Index data
  struct Menu *menu;              ///< Menu controlling the index
  struct MuttWindow *win_index;   ///< Window for the Index
};
```

---

More coming soon...

