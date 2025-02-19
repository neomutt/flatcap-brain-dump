## Compose Functions

<details>
<summary>Envelope</summary>

### Envelope

| Function              | OpCode                         | Description                                    |
| :-------------------- | :----------------------------- | :--------------------------------------------- |
| `<autocrypt-menu>`    | `OP_COMPOSE_AUTOCRYPT_MENU`    | show autocrypt compose menu options            |
| `<edit-bcc>`          | `OP_COMPOSE_EDIT_BCC`          | edit the BCC list                              |
| `<edit-cc>`           | `OP_COMPOSE_EDIT_CC`           | edit the CC list                               |
| `<edit-fcc>`          | `OP_COMPOSE_EDIT_FCC`          | enter a file to save a copy of this message in |
| `<edit-followup-to>`  | `OP_COMPOSE_EDIT_FOLLOWUP_TO`  | edit the Followup-To field                     |
| `<edit-from>`         | `OP_COMPOSE_EDIT_FROM`         | edit the from field                            |
| `<edit-newsgroups>`   | `OP_COMPOSE_EDIT_NEWSGROUPS`   | edit the newsgroups list                       |
| `<edit-reply-to>`     | `OP_COMPOSE_EDIT_REPLY_TO`     | edit the Reply-To field                        |
| `<edit-subject>`      | `OP_COMPOSE_EDIT_SUBJECT`      | edit the subject of this message               |
| `<edit-to>`           | `OP_COMPOSE_EDIT_TO`           | edit the TO list                               |
| `<edit-x-comment-to>` | `OP_COMPOSE_EDIT_X_COMMENT_TO` | edit the X-Comment-To field                    |
| `<pgp-menu>`          | `OP_COMPOSE_PGP_MENU`          | show PGP options                               |
| `<smime-menu>`        | `OP_COMPOSE_SMIME_MENU`        | show S/MIME options                            |

</details>
<details>
<summary>Email</summary>

### Email

| Function             | OpCode                        | Description                                         |
| :------------------- | :---------------------------- | :-------------------------------------------------- |
| `<edit-headers>`     | `OP_COMPOSE_EDIT_HEADERS`     | edit the message with headers                       |
| `<edit-message>`     | `OP_COMPOSE_EDIT_MESSAGE`     | edit the message                                    |
| `<ispell>`           | `OP_COMPOSE_ISPELL`           | run ispell on the message                           |
| `<mix>`              | `OP_COMPOSE_MIX`              | send the message through a mixmaster remailer chain |
| `<postpone-message>` | `OP_COMPOSE_POSTPONE_MESSAGE` | save this message to send later                     |
| `<send-message>`     | `OP_COMPOSE_SEND_MESSAGE`     | send the message                                    |
| `<write-fcc>`        | `OP_COMPOSE_WRITE_MESSAGE`    | write the message to a folder                       |

</details>
<details>
<summary>Misc</summary>

### Misc

| Function              | OpCode                         | Description                                    |
| :-------------------- | :----------------------------- | :--------------------------------------------- |
| `<display-toggle-weed>` | `OP_DISPLAY_HEADERS`   | display message and toggle header weeding |
| `<forget-passphrase>`   | `OP_FORGET_PASSPHRASE` | wipe passphrases from memory              |

</details>
<details>
<summary>Add Attachment</summary>

### Add Attachment

| Function                | OpCode                           | Description                                |
| :---------------------- | :------------------------------- | :----------------------------------------- |
| `<attach-file>`         | `OP_COMPOSE_ATTACH_FILE`         | attach files to this message               |
| `<attach-key>`          | `OP_COMPOSE_ATTACH_KEY`          | attach a PGP public key                    |
| `<attach-message>`      | `OP_COMPOSE_ATTACH_MESSAGE`      | attach messages to this message            |
| `<attach-news-message>` | `OP_COMPOSE_ATTACH_NEWS_MESSAGE` | attach news articles to this message       |
| `<new-mime>`            | `OP_COMPOSE_NEW_MIME`            | compose new attachment using mailcap entry |

</details>
<details>
<summary>Attachment Actions</summary>

### Attachment Actions

| Function               | OpCode                          | Description                                          |
| :--------------------- | :------------------------------ | :--------------------------------------------------- |
| `<copy-file>`          | `OP_SAVE`                       | save message/attachment to a mailbox/file            |
| `<detach-file>`        | `OP_DELETE`                     | delete the current entry                             |
| `<edit-description>`   | `OP_COMPOSE_EDIT_DESCRIPTION`   | edit attachment description                          |
| `<edit-encoding>`      | `OP_COMPOSE_EDIT_ENCODING`      | edit attachment transfer-encoding                    |
| `<edit-file>`          | `OP_COMPOSE_EDIT_FILE`          | edit the file to be attached                         |
| `<edit-language>`      | `OP_COMPOSE_EDIT_LANGUAGE`      | edit the 'Content-Language' of the attachment        |
| `<edit-mime>`          | `OP_COMPOSE_EDIT_MIME`          | edit attachment using mailcap entry                  |
| `<edit-type>`          | `OP_EDIT_TYPE`                  | edit attachment content type                         |
| `<filter-entry>`       | `OP_FILTER`                     | filter attachment through a shell command            |
| `<get-attachment>`     | `OP_COMPOSE_GET_ATTACHMENT`     | get a temporary copy of an attachment                |
| `<pipe-entry>`         | `OP_PIPE`                       | pipe message/attachment to a shell command           |
| `<print-entry>`        | `OP_PRINT`                      | print the current entry                              |
| `<rename-attachment>`  | `OP_COMPOSE_RENAME_ATTACHMENT`  | send attachment with a different name                |
| `<rename-file>`        | `OP_COMPOSE_RENAME_FILE`        | rename/move an attached file                         |
| `<toggle-disposition>` | `OP_COMPOSE_TOGGLE_DISPOSITION` | toggle disposition between inline/attachment         |
| `<toggle-recode>`      | `OP_COMPOSE_TOGGLE_RECODE`      | toggle recoding of this attachment                   |
| `<toggle-unlink>`      | `OP_COMPOSE_TOGGLE_UNLINK`      | toggle whether to delete file after sending it       |
| `<update-encoding>`    | `OP_COMPOSE_UPDATE_ENCODING`    | update an attachment's encoding info                 |
| `<view-attach>`        | `OP_VIEW_ATTACH`                | view attachment using mailcap entry if necessary     |

</details>
<details>
<summary>Attachment Organisation</summary>

### Attachment Organisation

| Function               | OpCode                          | Description                                          |
| :--------------------- | :------------------------------ | :--------------------------------------------------- |
| `<group-alternatives>` | `OP_COMPOSE_GROUP_ALTS`         | group tagged attachments as 'multipart/alternative'  |
| `<group-multilingual>` | `OP_COMPOSE_GROUP_LINGUAL`      | group tagged attachments as 'multipart/multilingual' |
| `<move-down>`          | `OP_COMPOSE_MOVE_DOWN`          | move an attachment down in the attachment list       |
| `<move-up>`            | `OP_COMPOSE_MOVE_UP`            | move an attachment up in the attachment list         |

</details>
<details>
<summary>Generic Movement</summary>

### Generic Movement

| Function             | OpCode                | Description                                   |
| :------------------- | :-------------------- | :-------------------------------------------- |
| `<bottom-page>`      | `OP_BOTTOM_PAGE`      | move to the bottom of the page                |
| `<current-bottom>`   | `OP_CURRENT_BOTTOM`   | move entry to bottom of screen                |
| `<current-middle>`   | `OP_CURRENT_MIDDLE`   | move entry to middle of screen                |
| `<current-top>`      | `OP_CURRENT_TOP`      | move entry to top of screen                   |
| `<first-entry>`      | `OP_FIRST_ENTRY`      | move to the first entry                       |
| `<half-down>`        | `OP_HALF_DOWN`        | scroll down 1/2 page                          |
| `<half-up>`          | `OP_HALF_UP`          | scroll up 1/2 page                            |
| `<jump>`             | `OP_JUMP`             | jump to an index number                       |
| `<last-entry>`       | `OP_LAST_ENTRY`       | move to the last entry                        |
| `<middle-page>`      | `OP_MIDDLE_PAGE`      | move to the middle of the page                |
| `<next-entry>`       | `OP_NEXT_ENTRY`       | move to the next entry                        |
| `<next-line>`        | `OP_NEXT_LINE`        | scroll down one line                          |
| `<next-page>`        | `OP_NEXT_PAGE`        | move to the next page                         |
| `<previous-entry>`   | `OP_PREV_ENTRY`       | move to the previous entry                    |
| `<previous-line>`    | `OP_PREV_LINE`        | scroll up one line                            |
| `<previous-page>`    | `OP_PREV_PAGE`        | move to the previous page                     |
| `<search>`           | `OP_SEARCH`           | search for a regular expression               |
| `<search-next>`      | `OP_SEARCH_NEXT`      | search for next match                         |
| `<search-opposite>`  | `OP_SEARCH_OPPOSITE`  | search for next match in opposite direction   |
| `<search-reverse>`   | `OP_SEARCH_REVERSE`   | search backwards for a regular expression     |
| `<top-page>`         | `OP_TOP_PAGE`         | move to the top of the page                   |

</details>
<details>
<summary>Generic Misc</summary>

### Generic Misc

| Function            | OpCode                    | Description                                    |
| :------------------ | :------------------------ | :--------------------------------------------- |
| `<check-stats>`     | `OP_CHECK_STATS`          | calculate message statistics for all mailboxes |
| `<end-cond>`        | `OP_END_COND`             | end of conditional execution (noop)            |
| `<enter-command>`   | `OP_ENTER_COMMAND`        | enter a neomuttrc command                      |
| `<exit>`            | `OP_EXIT`                 | exit this menu                                 |
| `<help>`            | `OP_HELP`                 | this screen                                    |
| `<refresh>`         | `OP_REDRAW`               | clear and redraw the screen                    |
| `<select-entry>`    | `OP_GENERIC_SELECT_ENTRY` | select the current entry                       |
| `<shell-escape>`    | `OP_SHELL_ESCAPE`         | invoke a command in a subshell                 |
| `<tag-entry>`       | `OP_TAG`                  | tag the current entry                          |
| `<tag-prefix-cond>` | `OP_TAG_PREFIX_COND`      | apply next function ONLY to tagged messages    |
| `<tag-prefix>`      | `OP_TAG_PREFIX`           | apply next function to tagged messages         |
| `<what-key>`        | `OP_WHAT_KEY`             | display the keycode for a key press            |

</details>
