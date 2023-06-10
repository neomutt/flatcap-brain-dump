| Domain                | Example               |
| :-------------------- | :-------------------- |
| NeoMutt (globals)     | version               |
| AccountView           | sort order            |
| Account               | name                  |
| MailboxView (Context) | current limit pattern |
| Mailbox               | path, size            |
| EmailView             | tagged                |
| Email                 | new                   |
| (None)                | padding, formatting   |
| Domain-specific       | compress hooks        |

<details><summary>alias_format_str</summary>

- `%a` Alias name
- `%f` Flags - currently, a 'd' for an alias marked for deletion
- `%n` Index number
- `%r` Address which alias expands to
- `%t` Character which indicates if the alias is tagged for inclusion
---
- `%>X` Right justify the rest of the string and pad with character `X`
- `%|X` Pad to the end of the line with character `X`
- `%*X` Soft-fill with character `X` as pad
---
- `$config` Expand NeoMutt config
- `$ENV` Expand an environment variable
- `pipe.sh|` Expand and run command
- `\x` Whitespace characters, carriage-return, line feed, etc
- ```` `backticks` ```` Execute command

</details>

<details><summary>attach_format_str</summary>

- `%C` Character set
- `%c` Character set: convert?
- `%D` Deleted flag
- `%d` Description
- `%e` MIME content-transfer-encoding
- `%f` Filename
- `%F` Filename for content-disposition header
- `%I` Content-disposition, either I (inline) or A (attachment)
- `%m` Major MIME type
- `%M` MIME subtype
- `%n` Attachment number
- `%Q` 'Q', if MIME part qualifies for attachment counting
- `%s` Size
- `%t` Tagged flag
- `%T` Tree chars
- `%u` Unlink
- `%X` Number of qualifying MIME parts in this part and its children
</details>

<details><summary>compose_format_str</summary>

- `%a` Total number of attachments
- `%h` Local hostname
- `%l` Approximate size (in bytes) of the current message
- `%v` NeoMutt version string
</details>

<details><summary>compress_format_str</summary>

- `%f` Compressed file
- `%t` Plaintext, temporary file
</details>

<details><summary>crypt_format_str</summary>

- `%a` Algorithm
- `%A` Algorithm of the principal key
- `%c` Capabilities
- `%C` Capabilities of the principal key
- `%f` Flags
- `%F` Flags of the principal key
- `%k` Key id
- `%K` Key id of the principal key
- `%l` Length
- `%L` Length of the principal key
- `%n` Number
- `%p` Protocol
- `%t` Trust/validity of the key-uid association
- `%u` User id
- `%[fmt]` Date of key using strftime(3)
</details>

<details><summary>fmt_pgp_command</summary>

- `%a` Value of `$pgp_sign_as` if set, otherwise `$pgp_default_key`
- `%f` File containing a message
- `%p` Expands to PGPPASSFD=0 when a pass phrase is needed, to an empty string otherwise
- `%r` One or more key IDs (or fingerprints if available)
- `%s` File containing the signature part of a multipart/signed attachment when verifying it
</details>

<details><summary>fmt_smime_command</summary>

- `%a` Algorithm used for encryption
- `%C` CA location: Depending on whether `$smime_ca_location` points to a directory or file
- `%c` One or more certificate IDs
- `%d` Message digest algorithm specified with `$smime_sign_digest_alg`
- `%f` File containing a message
- `%i` Intermediate certificates
- `%k` The key-pair specified with `$smime_default_key`
- `%s` File containing the signature part of a multipart/signed attachment when verifying it
</details>

<details><summary>folder_format_str</summary>

- `%C` Current file number
- `%d` Date/time folder was last modified
- `%D` Date/time folder was last modified using `$date_format.`
- `%F` File permissions
- `%f` Filename (with suffix `/`, `@` or `*`)
- `%g` Group name (or numeric gid, if missing)
- `%i` Description of the folder
- `%l` Number of hard links
- `%m` Number of messages in the mailbox
- `%N` N if mailbox has new mail, blank otherwise
- `%n` Number of unread messages in the mailbox
- `%s` Size in bytes
- `%t` `*` if the file is tagged, blank otherwise
- `%u` Owner name (or numeric uid, if missing)
</details>

<details><summary>group_index_format_str</summary>

- `%C` Current newsgroup number
- `%d` Description of newsgroup (becomes from server)
- `%f` Newsgroup name
- `%M` - if newsgroup not allowed for direct post (moderated for example)
- `%N` N if newsgroup is new, u if unsubscribed, blank otherwise
- `%n` Number of new articles in newsgroup
- `%s` Number of unread articles in newsgroup
</details>

<details><summary>history_format_str</summary>

- `%s` History match
</details>

<details><summary>index_format_str</summary>

- `%(fmt)` Date/time when the message was received
- `%a` Address of the author
- `%A` Reply-to address (if present; otherwise: address of author)
- `%b` Filename of the original message folder (think mailbox)
- `%B` The list to which the letter was sent, or else the folder name (%b)
- `%C` Current message number
- `%c` Number of characters (bytes) in the message
- `%D` Date and time of message using `$date_format` and local timezone
- `%d` Date and time of message using `$date_format` and sender's timezone
- `%e` Current message number in thread
- `%E` Number of messages in current thread
- `%Fp` Like %F, but plain. No contextual formatting is applied to recipient name
- `%F` Author name, or recipient name if the message is from you
- `%f` Sender (address + real name), either From: or Return-Path:
- `%Gx` Individual message tag (e.g. notmuch tags/imap flags)
- `%g` Message tags (e.g. notmuch tags/imap flags)
- `%H` Spam attribute(s) of this message
- `%I` Initials of author
- `%i` Message-id of the current message
- `%J` Message tags (if present, tree unfolded, and != parent's tags)
- `%K` The list to which the letter was sent (if any; otherwise: empty)
- `%L` Like %F, except 'lists' are displayed first
- `%l` Number of lines in the message
- `%M` Number of hidden messages if the thread is collapsed
- `%m` Total number of message in the mailbox
- `%n` Author's real name (or address if missing)
- `%N` Message score
- `%O` Like %L, except using address instead of name
- `%P` Progress indicator for the built-in pager (how much of the file has been displayed)
- `%q` Newsgroup name (if compiled with NNTP support)
- `%R` Comma separated list of Cc: recipients
- `%r` Comma separated list of To: recipients
- `%S` Single character status of the message (N/O/D/d/!/r/-)
- `%s` Subject of the message
- `%t` 'To:' field (recipients)
- `%T` The appropriate character from the `$to_chars` string
- `%u` User (login) name of the author
- `%v` First name of the author, or the recipient if the message is from you
- `%W` Name of organization of author ('Organization:' field)
- `%x` 'X-Comment-To:' field (if present and compiled with NNTP support)
- `%X` Number of MIME attachments
- `%y` 'X-Label:' field (if present)
- `%Y` 'X-Label:' field (if present, tree unfolded, and != parent's x-label)
- `%zc` Message crypto flags
- `%zs` Message status flags
- `%zt` Message tag flags
- `%Z` Combined message flags
- `%[fmt]` Message date/time converted to the local time zone
- `%{fmt}` Message date/time converted to sender's time zone
</details>

<details><summary>mix_format_str</summary>

- `%a` The remailer's e-mail address
- `%c` Remailer capabilities
- `%n` The running number on the menu
- `%s` The remailer's short name
</details>

<details><summary>nntp_format_str</summary>

- `%a` Account url
- `%p` Port
- `%P` Port if specified
- `%s` News server name
- `%S` Url schema
- `%u` Username
</details>

<details><summary>pgp_entry_fmt</summary>

- `%a` Algorithm
- `%A` Algorithm of the princ. key
- `%c` Capabilities
- `%C` Capabilities of the princ. key
- `%f` Flags
- `%F` Flags of the princ. key
- `%k` Key id
- `%K` Key id of the principal key
- `%l` Length
- `%L` Length of the princ. key
- `%n` Number
- `%t` Trust/validity of the key-uid association
- `%u` User id
- `%[fmt]` Date of key using strftime(3)
</details>

<details><summary>query_format_str</summary>

- `%a` Destination address
- `%c` Current entry number
- `%e` Extra information
- `%n` Destination name
- `%t` `*` if current entry is tagged, a space otherwise
</details>

<details><summary>sidebar_format_str</summary>

- `%!` 'n!' Flagged messages
- `%B` Name of the mailbox
- `%D` Description of the mailbox
- `%d` Number of deleted messages
- `%F` Number of Flagged messages in the mailbox
- `%L` Number of messages after limiting
- `%n` N if mailbox has new mail, blank otherwise
- `%N` Number of unread messages in the mailbox
- `%S` Size of mailbox (total number of messages)
- `%t` Number of tagged messages
</details>

<details><summary>status_format_str</summary>

- `%b` Number of incoming folders with unread messages
- `%D` Description of the mailbox
- `%d` Number of deleted messages
- `%f` Full mailbox path
- `%F` Number of flagged messages
- `%h` Hostname
- `%l` Length of mailbox (in bytes)
- `%L` Size (in bytes) of the messages shown
- `%M` Number of messages shown (virtual message count when limiting)
- `%m` Total number of messages
- `%n` Number of new messages
- `%o` Number of old unread messages
- `%p` Number of postponed messages
- `%P` Percent of way through index
- `%R` Number of read messages
- `%r` Readonly/wontwrite/changed flag
- `%S` Current aux sorting method (`$sort_aux`)
- `%s` Current sorting method (`$sort`)
- `%t` # of tagged messages
- `%u` Number of unread messages
- `%V` Currently active limit pattern
- `%v` NeoMutt version
</details>

