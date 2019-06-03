# NeoMutt Config Variables 3 - Inheritance

This is where things get interesting.
If you have any questions about them, please ask.

The simple changes give us a clean model for storing and manipulation config.

# Account

I'd like to introduce an Account object (for now, ignore the existing struct
of the same name).

The Account can be associated with a set of mailboxes.
It's initialised with a set of config items, e.g.
* folder
* spoolfile
* signature
* imap_user
* imap_pass

Initially, the Account's copy is empty (just a pointer to the global
version), but it can be set separately.

# Inheritance

Config item: "signature"

* Initial value: <empty>
* Global value: "~/.sig1"
* Account 1:    "~/.sig2"
* Account 2:    <unset> -> "~/.sig1"

The effect of reset on each variable is:

* Account 2: no change (it's already inherited)
* Account 1: value discarded, config becomes inherited
* Global: value discarded, config set to initial value

# Configuration

To handle accounts, I propose adding an "account" command with the following
syntax.

## Blocks

Create an account and set some config.
Any non-account config items will just set the global config as usual.
The "account" command ends with an empty "account" or at the end of the file.

This is useful for config files.

    account short-name
    set x = y
    set a = b
    account

## Lines

Set an account-specific config item.

    account short-name set x = y

This is useful within NeoMutt to change one config item.

https://github.com/flatcap/neomutt## Scoped

Use a scoping character ':' as a shortcut.
Set the variable within an account:

    set short-name:x = y

Set the variable within the current account:

    set :x = y

# State of Code

I've created a working example.  It covers all the types that NeoMutt uses
and it handles inheritance, validation and notifications.

    https://github.com/flatcap/neomutt

Notes:
* It's the result of a lot of hacking and cut'n'pasting.
* It's still under heavy development

---

Rich / FlatCap

