Help Mailbox

The Help Browser is a new feature to bring online help to NeoMutt.
The code is in the [devel/help](https://github.com/neomutt/neomutt/tree/devel/help) branch.

It adds a new config variable: `$help_doc_dir` which should point to a copy of the [`test-doc`](https://github.com/neomutt/test-doc) repo.
Help can be activated by pressing <kbd>Alt-H</kbd> and <kbd>Enter</kbd>

### To Do

- [ ] Split Code
   - [ ] List code
   - [ ] Scan
   - [ ] Mailbox
- [ ] De-globalise
   - [ ] Drop Cache
   - [ ] Move to Mailbox
- [ ] Config Variables
   - [ ] `$help_index_format`
   - [ ] `$help_simple_search`
   - [ ] `$hide_thread_subject`, `$sort`, `$sort_aux`
- [ ] User Interface
   - [ ] Hide YAML
   - [ ] Style Markdown
- [ ] Navigation
   - [ ] Parse help:// URIs
   - [ ] List links
   - [ ] Follow links

## Split Code

Currently, all the code is in a single file `help/help.c`.
The code would be easier to understand if it were split into three parts:

- List code
  Technically, it's a vector
  Once separated, this could be promoted to `libmutt` and used elsewhere

- Scanning code
  Move the code that scans a directory for markdown files.
  Ideally, this would return a sorted tree

- Mailbox code
  The core code that represents a Mailbox (`MxHelpOps`)

## Deglobalise

All the markdown files are processed into `Email`s and stored in the global `DocList`.
This acts as a cache, however, the Help files are unlikely to change during the run of NeoMutt.
The `Email`s should be attached to the `Mailbox` and have the same lifespan as it.

- Drop cache
- Attach all data to the `Account`, `Mailbox` or `Email`

![arch](https://flatcap.org/mutt/help.svg)

**Note**: `nftw()` needs a global component, but this can be hidden in the scan source file.

## Config Variables

The original plan was to add some extra config variables:

- `$help_index_format`
- `$help_simple_search`

and change the behaviour of some others:

- `$hide_thread_subject`
- `$sort`
- `$sort_aux`

On reflection, it may be better to use `Account`-specific config.
When the Help backend is initialised, it would create:

- `$help:index_format`
- `$help:simple_search`
- `$help:hide_thread_subject`
- `$help:sort`
- `$help:sort_aux`

## Other notes

- Global `HelpList *DocList`
  Array of `struct Email`
  `Email.edata` -\> `struct HelpDocMeta`

- `struct HelpDocMeta`
   Member `fhdr` (Array of `struct HelpList`)
   Array of (key,value) string pairs

- `struct Mailbox`
   Member `emails` (Array of `struct Email`)
   Threaded by references to message id
