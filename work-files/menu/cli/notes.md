# Parsing the CLI

## Help

Help options for info about Neomutt.
They are executed before any config is read.
(We want the help displayed, even if the config is bad)

They exit immediately.

    -h            Print this help message and exit
    -v            Print the NeoMutt version and compile-time definitions and exit
    -vv           Print the NeoMutt license and copyright information and exit

## Config

These options affect how config is loaded.

    -F <config>   Specify an alternative initialization file to read
    -n            Do not read the system-wide configuration file

## Logging

These options affect how and where NeoMutt logs.

    -d <level>    Log debugging output to a file (default is "~/.neomuttdebug0")
                  The level can range from 1-5 and affects verbosity
    -l <file>     Specify a file for debugging output (default "~/.neomuttdebug0")

## Info

These options query NeoMutt for configuration information.
They are executed after the config is read.
They exit after display.

    -A <alias>    Print an expanded version of the given alias to stdout and exit
    -D            Dump all config variables as 'name=value' pairs to stdout
    -D -D         (or -DD) Like -D, but only show changed config
    -D -O         Like -D, but show one-liner documentation
    -D -S         Like -D, but hide the value of sensitive variables
    -Q <variable> Query a configuration variable and print its value to stdout
                  (after the config has been read and any commands executed)
                  Add -O for one-liner documentation

## Send

These options allow the user to send email from the command line.
They **may** start the GUI to collect more info.

    -a <file>     Attach one or more files to a message (must be the last option)
                  Add any addresses after the '--' argument
    -b <address>  Specify a blind carbon copy (Bcc) recipient
    -c <address>  Specify a carbon copy (Cc) recipient
    -C            Enable Command-line Crypto (signing/encryption)
    -E            Edit draft (-H) or include (-i) file during message composition
    -e <command>  Specify a command to be run after reading the config files
    -H <draft>    Specify a draft file with header and body for message composing
    -i <include>  Specify an include file to be embedded in the body of a message
    -m <type>     Specify a default mailbox format type for newly created folders
                  The type is either MH, MMDF, Maildir or mbox (case-insensitive)
    -s <subject>  Specify a subject (must be enclosed in quotes if it has spaces)
    [non-option]  Additional arguments
    --            Special argument forces NeoMutt to stop option parsing and treat
                  remaining arguments as addresses even if they start with a dash

## GUI

These queries **optionally** start the GUI.

    -Z            Open the first mailbox with new message or exit immediately with
                  exit code 1 if none is found in all defined mailboxes
    -z            Open the first or specified (-f) mailbox if it holds any message
                  or exit immediately with exit code 1 otherwise

These options affect the startup of the GUI.

    -e <command>  Specify a command to be run after reading the config files
    -f <mailbox>  Specify a mailbox (as defined with 'mailboxes' command) to load
    -G            Start NeoMutt with a listing of subscribed newsgroups
    -g <server>   Like -G, but start at specified news server
    -m <type>     Specify a default mailbox format type for newly created folders
                  The type is either MH, MMDF, Maildir or mbox (case-insensitive)
    -p            Resume a prior postponed message, if any
    -R            Open mailbox in read-only mode
    -y            Start NeoMutt with a listing of all defined mailboxes

## Priority

The six CLI option groups have to be considered in order:

- **Parse**: Parse the Command Line into structs, but don't perform any actions yet

- **Help**: If help options are given
    - Display help
    - Exit

- **Early Logging**: Open the log file
  (honouring the `-d` and `-l` options)

- **Config**: Read the system and user config files
  (honouring the `-n` and `-F` options)

- **Late Logging**: Open the log file
  (honouring the config)

- **Info**: If info options are given
    - Display info
    - Exit

- **Send**: Send an email from the Command Line
    - GUI: Gather more info (optional)
    - Send email
    - Exit

- **GUI**: Start the NeoMutt GUI
  The options affect where the user starts, e.g.
  - `-p` Postponed emails
  - `-y` Mailbox browser

## Notes

- libcli => testable
- one cli struct, with 6 children (abstract)
  fn to clear the contents

- `-A` absorbs following args too, e.g.
  `-A apple banana cherry`

- `-m` applies to Send and GUI modes
  (could affect the `fcc:` mailbox)

gahr
    NeoMutt has four modes of operation: help, info, send, and gui. The default
    mode if no command line argument is specified is gui. The following options
    can be applied to all four modes: <config and logging sections here>.

    The following four sections detail the options available in each of the mode
    of operation. Options from different sections cannot be specified together:
    <the other sections>

shared
help
info
send
gui

lowercase sentence after "section:"

