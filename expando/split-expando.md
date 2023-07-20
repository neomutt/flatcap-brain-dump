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

Implements ::format_t - @ingroup expando_api

20

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

