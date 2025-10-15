Send Signed/Encrypted Email from the Command Line

NeoMutt's startup code is a mess that needs sorting out.
But not today.

Below is a very quick look at sending an email from the command line.
What the code does, what affects the flow.

---

Affected by:
- `configure` options, e.g. `--gpgme`
- Environment, e.g. `$MAIL`
- `/etc/passwd` for real name

Command line parameters:
- `-b bcc` (multiple)
- `-c cc` (multiple)
- `john@example.com` (multiple addresses)
- stdin (`< text`)
- `-s subject`
- `-i text` (interactive)
- `-H draft` (interactive)
- `-p` (postponed, interactive)

Need options to sign/encrypt/both

Config
- `-F ~/.neomuttrc`
- `-e "commands"`

Startup:

- `main()`
- `crypt_init()` - `$crypt_use_gpgme`

Create template:
- `e = email_new()`
- `env = env_new()`

Parse addresses
- `mutt_parse_mailto()` or `mutt_addrlist_parse()`

Time to send the email: `mutt_send_message(SEND_BATCH, e)`

Create body:
- body = `body_new()`
  - `$content_type` (text/plain)
  - `mutt_parse_content_type()`

Temp file for body text:
- `fp_tmp` = `buf_mktemp()`

Config
- `$resume_draft_files`
- `$hdrs`

Prep envelope
- `mutt_expand_aliases_env()`
- `mutt_default_from()`

Hook
- `send-hook`

Prep envelope
- `$use_from`
- `mutt_default_from()`
- `process_user_header()`

Populate body
- `mutt_file_copy_stream(stdin)` -> `fp_tmp`

Add body extras, e.g. attach key
- `generate_body()`
   - noop

Config
- `$text_flowed`

Hook
- `send2-hook`

Prep envelope
- `$real_name`

The patch affects the code here, removing a `!SEND_BATCH` check

Crypto setup
- `$autocrypt`
- `$crypt_auto_sign`
- `$crypt_auto_encrypt`
- `$crypt_reply_encrypt`
- `$crypt_reply_sign`
- `$crypt_reply_sign_encrypted`
- `$crypt_opportunistic_encrypt`
- Flag Body with `SEC_SIGN | SEC_ENCRYPT`

Prep saving sent email
- `$copy`
- `select_fcc()`

Prep email for sending
- `mutt_rfc3676_space_stuff()`
- `mutt_update_encoding()`
- `mutt_env_to_intl()`
- `mutt_encode_descriptions()`

Apply crypto settings

Send email
- `mutt_prepare_envelope()`
- `invoke_mta()`
- `save_fcc()`

