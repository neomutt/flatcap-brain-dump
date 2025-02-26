## Hostname Uses

NeoMutt uses two forms of the hostname:

The **Hostname**, e.g. 'laptop.example.com', is only referenced by `mutt_fqdn()`, which is used to:
- expanding aliases
- determine if an address is _you_
- match encryption keys
- expand outgoing email addresses

The **ShortHostname**, e.g. 'laptop', is used to:
- generate the Message-ID header
- generate some unique temporary filenames
- fallback if the FQDN is missing

## Hostname Sources

To find the hostname the code checks multiple sources in order.
Note: There's no default in `init.h`

1. Config file
   - /etc/neomuttrc
   - ~/.neomuttrc

2. Command line
   - `neomutt -e "set hostname=laptop.example.com"`

3. uname(2)
   - set the ShortHostname (e.g. 'laptop')

4.  First match of:
     1. configured DOMAIN
        `configure --with-domain=example.com`

     2. file
        - `/etc/mailname`
        - `/etc/mail/mailname`

     3. dns
        - `gethostname()` -- For a hostname
        - `getaddrinfo()` or `getaddrinfo_a()` -- For a FQDN

