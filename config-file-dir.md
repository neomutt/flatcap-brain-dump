- Add `DT_DIR` and `DT_FILE` to config items
- Filter out trailing `/`
- Check they exist (if required) with `DT_MUST_EXIST`
- Create (if required) with `DT_CREATE`

**DIR**

| Config Item        | Type                | Default Value     |
| :----------------- | :------------------ | :---------------- |
| attach_save_dir    | `DT_STRING|DT_PATH` | ./                |
| autocrypt_dir      | `DT_STRING|DT_PATH` | ~/.mutt/autocrypt |
| message_cachedir   | `DT_STRING|DT_PATH` |                   |
| news_cache_dir     | `DT_STRING|DT_PATH` | ~/.neomutt        |
| smime_certificates | `DT_STRING|DT_PATH` |                   |
| smime_keys         | `DT_STRING|DT_PATH` |                   |
| tmpdir             | `DT_STRING|DT_PATH` | /tmp              |

**FILE**

| Config Item              | Type                | Default Value        |
| :----------------------- | :------------------ | :------------------- |
| alias_file               | `DT_STRING|DT_PATH` | ~/.neomuttrc         |
| certificate_file         | `DT_STRING|DT_PATH` | ~/.mutt_certificates |
| debug_file               | `DT_STRING|DT_PATH` | ~/.neomuttdebug      |
| entropy_file             | `DT_STRING|DT_PATH` |                      |
| history_file             | `DT_STRING|DT_PATH` | ~/.mutthistory       |
| newsrc                   | `DT_STRING|DT_PATH` | ~/.newsrc            |
| signature                | `DT_STRING|DT_PATH` | ~/.signature         |
| ssl_ca_certificates_file | `DT_STRING|DT_PATH` |                      |
| ssl_client_cert          | `DT_STRING|DT_PATH` |                      |

**EITHER**

| Config Item       | Type                | Default Value |
| :---------------- | :------------------ | :------------ |
| header_cache      | `DT_STRING|DT_PATH` |               |
| smime_ca_location | `DT_STRING|DT_PATH` |               |

**MAILBOX/FILE**

| Config Item | Type                           | Default Value |
| :---------- | :----------------------------- | :------------ |
| folder      | `DT_STRING|DT_PATH|DT_MAILBOX` | ~/Mail        |
| postponed   | `DT_STRING|DT_PATH|DT_MAILBOX` | ~/postponed   |
| record      | `DT_STRING|DT_PATH|DT_MAILBOX` | ~/sent        |
| spoolfile   | `DT_STRING|DT_PATH|DT_MAILBOX` |               |
| trash       | `DT_STRING|DT_PATH|DT_MAILBOX` |               |

