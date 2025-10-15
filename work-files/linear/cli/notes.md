# Parsing the CLI

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

