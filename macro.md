# Encapsulation with `<macro>` ... `<macro-end>` functions

> This thought's just occurred to me.  I'm not _quite_ sure how we'd implement, yet.

Allow the user to run `<tag-prefix>` on a **marked** set of functions.

## Premise

### Naive Macro

A NeoMutt beginner creates a `macro` for the Index.

```perl
# Mark the Email as New and Flag it
macro index <F4> '<set-flag>N<set-flag>!'
```

It doesn't work, because `set resolve = yes` and the cursor moves between setting flags.

### Improved Macro

Fortunately, the user's a smart cookie.  They try saving/restoring `$resolve`:

```perl
# Mark the Email as New and Flag it
# Save $resolve and restore it afterwards
macro index <F4> '<enter-command>set my_resolve=$resolve resolve=no<enter><set-flag>N<enter-command>set resolve=$my_resolve<enter><set-flag>!'
```

Very pleased with themselves, they try to run it on a bunch of tagged Emails: <kbd>;</kbd><kbd>\<F4\></kbd> (<kbd>\<tag-prefix\></kbd><kbd>\<F4\></kbd>)

The result is that only the current Email is affected.

## Improvement

We could create a pair of functions: `<macro>` and `<macro-end>` to wrap a set of functions.
They would be executed atomically.

```perl
macro index <F4> '<macro><set-flag>N<set-flag>!<macro-end>'
```

### Simple Use

NeoMutt would execute `<set-flag>` twice, **then** honour `$resolve` (moving the cursor).

### Tagged Use

When used with `<tag-prefix>`, NeoMutt would perform **both** the actions on **all** the tagged Emails.

## Finesse

To make a robust `macro`, sometimes it's necessary to save/restore config options.
Above, we save the value of `$resolve` into a `my_var`.

The Config System supports Subsets -- invented to support Account- and Mailbox-level config (not yet implemented).

These could be used to allow temporary config changes, in `macro`s.
e.g.

```perl
macro index <F4> '<config-save><enter-command>set real_name="John Smith"<enter> [DO SOMETHING] <config-restore>'
```

