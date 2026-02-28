### 💬 Copilot

Here are the most useful missing readline-like functions, grouped by category:

---

### 🔴 High Impact — Kill Ring / Yank

The existing `kill-*` functions discard text into a void. Without yank, users permanently lose killed text.

| Function | Readline binding | Description |
|---|---|---|
| `yank` | `Ctrl-Y` | Paste last killed text at cursor |
| `yank-pop` | `Alt-Y` | After yank, rotate to the previous kill |

Requires adding a kill ring (even a single-entry one) to `EnterWindowData` / `EnterState`.

---

### 🔴 High Impact — Undo

| Function | Readline binding | Description |
|---|---|---|
| `undo` | `Ctrl-_` | Undo last editing action |

Readline's undo stack tracks every change to the line. Even a shallow undo (one level) would be very useful.

---

### 🟡 Medium Impact — Mark/Region

| Function | Readline binding | Description |
|---|---|---|
| `set-mark` | `Ctrl-@` / `Ctrl-Space` | Set the mark at the cursor position |
| `kill-region` | `Ctrl-W` (emacs) | Delete text between mark and cursor, saving to kill ring |
| `copy-region-as-kill` | `Alt-W` | Copy text between mark and cursor to kill ring without deleting |
| `exchange-point-and-mark` | `Ctrl-X Ctrl-X` | Swap cursor and mark positions |

Requires adding a `mark` field to `EnterState`.

---

### 🟡 Medium Impact — History

| Function | Readline binding | Description |
|---|---|---|
| `yank-last-arg` | `Alt-.` / `Alt-_` | Insert the last word of the previous history entry; repeat to walk back further |
| `yank-nth-arg` | `Alt-Ctrl-Y` | Insert the *n*th word from the previous history entry |
| `revert-line` | `Alt-R` | Undo all changes to the current line, restoring the original history entry |

`yank-last-arg` is especially useful when reusing a recently visited mailbox name.

---

### 🟡 Medium Impact — Search / Navigation

| Function | Readline binding | Description |
|---|---|---|
| `character-search` | `Ctrl-]` | Read a char, then jump forward to its next occurrence on the line |
| `character-search-backward` | `Alt-Ctrl-]` | Same, but search backward |
| `forward-search-history` | `Ctrl-S` | Incremental forward history search (complement to `history-search`/`Ctrl-R`) |

---

### 🟢 Lower Impact — Misc

| Function | Readline binding | Description |
|---|---|---|
| `delete-horizontal-space` | `Alt-\` | Delete all whitespace around the cursor |
| `tilde-expand` | `Alt-~` | Expand a leading `~` to the home directory |
| `insert-comment` | `Alt-#` | Prepend `#` and submit — useful in command prompt to "comment out" a command and save it to history without executing |
| `digit-argument` | `Alt-0`…`Alt-9` | Numeric argument multiplier for the next command (e.g. `Alt-5 forward-char` moves 5 chars) |

---

### Summary by effort vs. value

| Priority | Function(s) | Why |
|---|---|---|
| Must-have | `yank` | Killed text is currently gone forever |
| Must-have | `undo` | Standard expectation in any line editor |
| High value | `set-mark` + `kill-region` + `copy-region-as-kill` | Enables precise region editing |
| High value | `yank-last-arg` | Common workflow when reusing filenames/addresses |
| Nice-to-have | `character-search` | Fast in-line navigation |
| Nice-to-have | `revert-line` | Useful when navigating history |

