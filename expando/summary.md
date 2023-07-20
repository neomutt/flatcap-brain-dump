<details>
<summary>$alias_format_str (6)</summary>

**Source**: [alias/dlg_alias.c:113:60:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/alias/dlg_alias.c#L112-L123)

| Expando | Description                                                    |
| :------ | :-------------------------------------------------------       |
| %a      | Alias name                                                     |
| %c      | Comments                                                       |
| %f      | Flags - currently, a 'd' for an alias marked for deletion      |
| %n      | Index number                                                   |
| %r      | Address which alias expands to                                 |
| %t      | Character which indicates if the alias is tagged for inclusion |

</details>

<details>
<summary>$query_format_str (5)</summary>

**Source**: [alias/dlg_query.c:140:60:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/alias/dlg_query.c#L139-L149)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %a      | Destination address                                      |
| %c      | Current entry number                                     |
| %e      | Extra information                                        |
| %n      | Destination name                                         |
| %t      | `*` if current entry is tagged, a space otherwise        |

</details>

<details>
<summary>$attach_format_str (17)</summary>

**Source**: [attach/dlg_attach.c:131:66:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/attach/dlg_attach.c#L130-L152)

| Expando | Description                                                   |
| :------ | :-------------------------------------------------------      |
| %C      | Character set                                                 |
| %c      | Character set: convert?                                       |
| %D      | Deleted flag                                                  |
| %d      | Description                                                   |
| %e      | MIME content-transfer-encoding                                |
| %f      | Filename                                                      |
| %F      | Filename for content-disposition header                       |
| %I      | Content-disposition, either I (inline) or A (attachment)      |
| %m      | Major MIME type                                               |
| %M      | MIME subtype                                                  |
| %n      | Attachment number                                             |
| %Q      | 'Q', if MIME part qualifies for attachment counting           |
| %s      | Size                                                          |
| %t      | Tagged flag                                                   |
| %T      | Tree chars                                                    |
| %u      | Unlink                                                        |
| %X      | Number of qualifying MIME parts in this part and its children |

</details>

<details>
<summary>$autocrypt_format_str (5)</summary>

**Source**: [autocrypt/dlg_autocrypt.c:114:76:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/autocrypt/dlg_autocrypt.c#L113-L123)

| Expando | Description                                                       |
| :------ | :---------------------------------------------------------------- |
| %a      | Email address                                                     |
| %k      | Gpg keyid                                                         |
| %n      | Current entry number                                              |
| %p      | Prefer-encrypt flag                                               |
| %s      | Status flag (active/inactive)                                     |

</details>

<details>
<summary>$folder_format_str (15)</summary>

**Source**: [browser/dlg_browser.c:190:65:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/browser/dlg_browser.c#L189-L209)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %C      | Current file number                                      |
| %d      | Date/time folder was last modified                       |
| %D      | Date/time folder was last modified using `$date_format.` |
| %F      | File permissions                                         |
| %f      | Filename (with suffix `/`, `@` or `*`)                   |
| %g      | Group name (or numeric gid, if missing)                  |
| %i      | Description of the folder                                |
| %l      | Number of hard links                                     |
| %m      | Number of messages in the mailbox                        |
| %N      | "N" if mailbox has new mail, " " (space) otherwise       |
| %n      | Number of unread messages in the mailbox                 |
| %s      | Size in bytes                                            |
| %t      | `*` if the file is tagged, blank otherwise               |
| %u      | Owner name (or numeric uid, if missing)                  |
| %[fmt]  | Date folder was last modified using strftime(3)          |

</details>

<details>
<summary>$compress_format_str (2)</summary>

**Source**: [compmbox/compress.c:248:69:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/compmbox/compress.c#L247-L254)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %f      | Compressed file                                          |
| %t      | Plaintext, temporary file                                |

</details>

<details>
<summary>$compose_format_str (4)</summary>

**Source**: [compose/cbar.c:95:73:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/compose/cbar.c#L94-L103)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %a      | Total number of attachments                              |
| %h      | Local hostname                                           |
| %l      | Approximate size (in bytes) of the current message       |
| %v      | NeoMutt version string                                   |

</details>

<details>
<summary>$index_format_str (51)</summary>

**Source**: [hdrline.c:338:60:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/hdrline.c#L337-L393)

| Expando    | Description                                                                         |
| :------    | :----------------------------------------------------------------                   |
| %a         | Address of the author                                                               |
| %A         | Reply-to address (if present; otherwise: address of author)                         |
| %b         | Filename of the original message folder (think mailbox)                             |
| %B         | The list to which the email was sent, or else the folder name (%b)                  |
| %C         | Current message number                                                              |
| %c         | Number of characters (bytes) in the body of the message                             |
| %cr        | Number of characters (bytes) in the message, including header                       |
| %D         | Date and time of message using `$date_format` and local timezone                    |
| %d         | Date and time of message using `$date_format` and sender's timezone                 |
| %e         | Current message number in thread                                                    |
| %E         | Number of messages in current thread                                                |
| %Fp        | Like %F, but plain. No contextual formatting is applied to recipient name           |
| %F         | Author name, or recipient name if the message is from you                           |
| %f         | Sender (address + real name), either From: or Return-Path:                          |
| %Gx        | Individual message tag (e.g. notmuch tags/imap flags)                               |
| %g         | Message tags (e.g. notmuch tags/imap flags)                                         |
| %H         | Spam attribute(s) of this message                                                   |
| %I         | Initials of author                                                                  |
| %i         | Message-id of the current message                                                   |
| %J         | Message tags (if present, tree unfolded, and != parent's tags)                      |
| %K         | The list to which the email was sent (if any; otherwise: empty)                     |
| %L         | Like %F, except 'lists' are displayed first                                         |
| %l         | Number of lines in the message                                                      |
| %M         | Number of hidden messages if the thread is collapsed                                |
| %m         | Total number of message in the mailbox                                              |
| %n         | Author's real name (or address if missing)                                          |
| %N         | Message score                                                                       |
| %O         | Like %L, except using address instead of name                                       |
| %P         | Progress indicator for the built-in pager (how much of the file has been displayed) |
| %q         | Newsgroup name (if compiled with NNTP support)                                      |
| %R         | Comma separated list of Cc: recipients                                              |
| %r         | Comma separated list of To: recipients                                              |
| %S         | Single character status of the message (N/O/D/d/!/r/-)                              |
| %s         | Subject of the message                                                              |
| %t         | 'To:' field (recipients)                                                            |
| %T         | The appropriate character from the `$to_chars` string                               |
| %u         | User (login) name of the author                                                     |
| %v         | First name of the author, or the recipient if the message is from you               |
| %W         | Name of organization of author ('Organization:' field)                              |
| %x         | 'X-Comment-To:' field (if present and compiled with NNTP support)                   |
| %X         | Number of MIME attachments                                                          |
| %y         | 'X-Label:' field (if present)                                                       |
| %Y         | 'X-Label:' field (if present, tree unfolded, and != parent's x-label)               |
| %zc        | Message crypto flags                                                                |
| %zs        | Message status flags                                                                |
| %zt        | Message tag flags                                                                   |
| %Z         | Combined message flags                                                              |
| %`@name@`  | Insert and evaluate format-string from the matching "$index-format-hook" command    |
| %(fmt)     | Date/time when the message was received                                             |
| %[fmt]     | Message date/time converted to the local time zone                                  |
| %{fmt}     | Message date/time converted to sender's time zone                                   |

</details>

<details>
<summary>$history_format_str (1)</summary>

**Source**: [history/dlg_history.c:86:64:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/history/dlg_history.c#L85-L91)

| Expando | Description    |
| :------ | :------------- |
| %s      | History match  |

</details>

<details>
<summary>$mix_format_str (4)</summary>

**Source**: [mixmaster/win_hosts.c:110:61:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/mixmaster/win_hosts.c#L109-L118)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %a      | The remailer's e-mail address                            |
| %c      | Remailer capabilities                                    |
| %n      | The running number on the menu                           |
| %s      | The remailer's short name                                |

</details>

<details>
<summary>$crypt_format_str (17)</summary>

**Source**: [ncrypt/dlg_gpgme.c:339:68:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/ncrypt/dlg_gpgme.c#L338-L362)

| Expando | Description                                                           |
| :------ | :-------------------------------------------------------              |
| %n      | Number                                                                |
| %p      | Protocol                                                              |
| %t      | Trust/validity of the key-uid association                             |
| %u      | User id                                                               |
| %[fmt]  | Date of key using strftime(3)                                         |
|         |                                                                       |
| %a      | Algorithm                                                             |
| %c      | Capabilities                                                          |
| %f      | Flags                                                                 |
| %i      | Key fingerprint (or long key id if non-existent)                      |
| %k      | Key id                                                                |
| %l      | Length                                                                |
|         |                                                                       |
| %A      | Algorithm of the principal key                                        |
| %C      | Capabilities of the principal key                                     |
| %F      | Flags of the principal key                                            |
| %I      | Key fingerprint of the principal key (or long key id if non-existent) |
| %K      | Key id of the principal key                                           |
| %L      | Length of the principal key                                           |

</details>

<details>
<summary>$pgp_entry_format_str (14)</summary>

**Source**: [ncrypt/dlg_pgp.c:319:75:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/ncrypt/dlg_pgp.c#L318-L339)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %n      | Number                                                   |
| %t      | Trust/validity of the key-uid association                |
| %u      | User id                                                  |
| %[fmt]  | Date of key using strftime(3)                            |
|         |                                                          |
| %a      | Algorithm                                                |
| %c      | Capabilities                                             |
| %f      | Flags                                                    |
| %k      | Key id                                                   |
| %l      | Length                                                   |
|         |                                                          |
| %A      | Algorithm of the principal key                           |
| %C      | Capabilities of the principal key                        |
| %F      | Flags of the principal key                               |
| %K      | Key id of the principal key                              |
| %L      | Length of the principal key                              |

</details>

<details>
<summary>$pgp_command_format_str (5)</summary>

**Source**: [ncrypt/pgpinvoke.c:69:59:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/ncrypt/pgpinvoke.c#L68-L78)

| Expando | Description                                                                           |
| :------ | :----------------------------------------------------------------                     |
| %a      | Value of `$pgp_sign_as` if set, otherwise `$pgp_default_key`                          |
| %f      | File containing a message                                                             |
| %p      | Expands to PGPPASSFD=0 when a pass phrase is needed, to an empty string otherwise     |
| %r      | One or more key IDs (or fingerprints if available)                                    |
| %s      | File containing the signature part of a multipart/signed attachment when verifying it |

</details>

<details>
<summary>$smime_command_format_str (8)</summary>

**Source**: [ncrypt/smime.c:210:57:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/ncrypt/smime.c#L209-L222)

| Expando | Description                                                                           |
| :------ | :----------------------------------------------------------------                     |
| %a      | Algorithm used for encryption                                                         |
| %C      | CA location: Depending on whether `$smime_ca_location` points to a directory or file  |
| %c      | One or more certificate IDs                                                           |
| %d      | Message digest algorithm specified with `$smime_sign_digest_alg`                      |
| %f      | File containing a message                                                             |
| %i      | Intermediate certificates                                                             |
| %k      | The key-pair specified with `$smime_default_key`                                      |
| %s      | File containing the signature part of a multipart/signed attachment when verifying it |

</details>

<details>
<summary>$group_index_format_str (7)</summary>

**Source**: [nntp/browse.c:43:70:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/nntp/browse.c#L42-L54)

| Expando | Description                                                        |
| :------ | :-------------------------------------------------------           |
| %C      | Current newsgroup number                                           |
| %d      | Description of newsgroup (becomes from server)                     |
| %f      | Newsgroup name                                                     |
| %M      | - if newsgroup not allowed for direct post (moderated for example) |
| %N      | N if newsgroup is new, u if unsubscribed, blank otherwise          |
| %n      | Number of new articles in newsgroup                                |
| %s      | Number of unread articles in newsgroup                             |

</details>

<details>
<summary>$nntp_format_str (6)</summary>

**Source**: [nntp/newsrc.c:916:51:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/nntp/newsrc.c#L915-L926)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %a      | Account url                                              |
| %p      | Port                                                     |
| %P      | Port if specified                                        |
| %s      | News server name                                         |
| %S      | Url schema                                               |
| %u      | Username                                                 |

</details>

<details>
<summary>$pattern_format_str (3)</summary>

**Source**: [pattern/dlg_pattern.c:99:75:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/pattern/dlg_pattern.c#L98-L106)

| Expando | Description            |
| :------ | :--------------------- |
| %d      | Pattern description    |
| %e      | Pattern expression     |
| %n      | Index number           |

</details>

<details>
<summary>$greeting_format_str (3)</summary>

**Source**: [send/send.c:671:54:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/send/send.c#L670-L678)

| Expando | Description                                                       |
| :------ | :---------------------------------------------------------------- |
| %n      | Recipient's real name (or address if missing)                     |
| %u      | User (login) name of the recipient                                |
| %v      | First name of the recipient                                       |

</details>

<details>
<summary>$sidebar_format_str (13)</summary>

**Source**: [sidebar/window.c:330:59:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/sidebar/window.c#L329-L347)

| Expando | Description                                              |
| :------ | :------------------------------------------------------- |
| %!      | 'n!' Flagged messages                                    |
| %B      | Name of the mailbox                                      |
| %D      | Description of the mailbox                               |
| %d      | Number of deleted messages                               |
| %F      | Number of Flagged messages in the mailbox                |
| %L      | Number of messages after limiting                        |
| %n      | "N" if mailbox has new mail, " " (space) otherwise       |
| %N      | Number of unread messages in the mailbox                 |
| %o      | Number of old unread messages in the mailbox             |
| %r      | Number of read messages in the mailbox                   |
| %S      | Size of mailbox (total number of messages)               |
| %t      | Number of tagged messages                                |
| %Z      | Number of new unseen messages in the mailbox             |

</details>

<details>
<summary>$status_format_str (23)</summary>

**Source**: [status.c:72:55:](https://github.com/neomutt/neomutt/blob/a2917814bcae00cf294c2596d82f00282e60d7cc/status.c#L71-L99)

| Expando | Description                                                    |
| :------ | :-------------------------------------------------------       |
| %b      | Number of incoming folders with unread messages                |
| %D      | Description of the mailbox                                     |
| %d      | Number of deleted messages                                     |
| %f      | Full mailbox path                                              |
| %F      | Number of flagged messages                                     |
| %h      | Hostname                                                       |
| %l      | Length of mailbox (in bytes)                                   |
| %L      | Size (in bytes) of the messages shown (or limited)             |
| %M      | Number of messages shown (virtual message count when limiting) |
| %m      | Total number of messages                                       |
| %n      | Number of new messages                                         |
| %o      | Number of old unread messages                                  |
| %p      | Number of postponed messages                                   |
| %P      | Percent of way through index                                   |
| %R      | Number of read messages                                        |
| %r      | Readonly/wontwrite/changed flag                                |
| %S      | Current aux sorting method (`$sort_aux`)                       |
| %s      | Current sorting method (`$sort`)                               |
| %T      | Current threading view (`$use_threads`)                        |
| %t      | Number of tagged messages                                      |
| %u      | Number of unread messages                                      |
| %V      | Currently active limit pattern                                 |
| %v      | NeoMutt version                                                |

</details>

