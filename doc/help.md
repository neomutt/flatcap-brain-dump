## Help files

All in markdown with YAML headers
Chapters/sections stored in directories
Each directory has a directory.md as a title page
Root directory has an index.md

- index.md
- apple.md
- apple/
	+ banana.md
	+ cherry.md
	+ damson.md

## Parsing the help directory

- Should be simple
- Recurse through directories and find markdown files
- Store the results in a generic tree structure
- No sorting
- Use nftw()
- Only dependency is libmutt.a
- Unit-testable

Something like:

```c
struct HelpDir
{
    const char *name;
    struct HelpDir *subdirs[];
    const char *markdown[];
};

struct HelpTree
{
    const char *path;
    struct HelpDir *root;
};
```

## YAML Headers

Every help file will have a YAML header, with a selection of fields.
Some mandatory\* fields, the others optional

- layout\*        - Used by website
- title\*         - Short name used by chapter or section
- description\*   - Longer descriptive sentence
- keywords        - Words that don't appear in the text, but should match in searches
- last updated    - Timestamp of last change
- last updated by - Person who made the last change
- labels          - Text labels creating categories for the help files
- maintainer      - Person to be notified on change

## Mapping NeoMutt Structures

Next we take the HelpTree and map it to NeoMutt structures:
- Header
- Envelope
- MuttThread

As a 'fake' mailbox, many fields won't get used, and some will get abused.

- `struct Header` - Each markdown file
- `struct MuttThread` - Each directory, linking the `Header`s
- `struct Envelope` - YAML headers

Recurse through our HelpTree, reading the YAML header for each file.

### NeoMutt

**struct Header**:
- offset - File offset of first line after YAML header
- date_sent - Timestamp of last update
- score - Search score (a measure of search relevance).
- path - Location of file

**struct Envelope**:
- subject / 
- disp_subject

**struct Thread**:
- Interlinked headers

### YAML

- layout - ignore
- title - Envelope->subject
- description - cat title and description -> Envelope->disp_subject
- keywords - Envelope->userhdrs
- last updated - Envelope->date_sent, Envelope->received
- last updated by - Envelope->cc
- label - Header->tags

Some of these header fields might be generated from the git repo at install time.

## Header Format

As the help is completely different to other mailboxes, it needs its own format
string: `$help_format`.

| Expando | Description  |
| :------ | :----------- |
| %t      | title        |
| %d      | description  |
| %k      | keywords     |
| %u      | last updated |
| %p      | path         |
| %l      | labels       |
| %C      | index number |
| %B      | size (bytes) |
| %L      | size (lines) |
| %W      | size (words) |
| %s      | section      |

Last updated timestamp could be relative: "4 days ago"

## Ideas / Questions / Notes

Ideas and questions in no particular order:

- Drop md5 comparison
  md5 is quite expensive and the paths are quite short.
  `strcmp()` will do.

- Command line option `--guide`
  Open in the help mailbox.
  `sidebar=no`, `pager_index_lines=10`

- Need cleanup function to release the HelpTree in `mutt_free_opts()`

- Caching: It is worth it?
  - How long does it take to read a directory of a few hundred files?
  - How much space will the HelpTree take up?
  - How long does it take to parse a few hundred files?
  - How much space will the Headers take up?

- Allow pages to have attachments (in the header)
  e.g. images -> mailcap viewer

- Change the <kbd>Alt-H</kbd> mapping to:
  `macro \eH <help><enter>`
  For the beginner, the help comes up.

- Have a 'magic' help page!
  `macro \eR <help>RANDOM<enter>`

- Maintainer field in YAML
  When a page is updated, this person is notified.
  'cc' them when changing by email.
  Use travis for web alterations.

- Current Docs have
  -  39 \<chapter\>
  - 282 \<sect1\>
  - 511 \<sect2\>
  -  24 \<sect3\>
  -   4 \<sect4\>
  -   2 \<sect5\>

## To Do

- More YAML headers for test docs
- Better data too

