NEO	?= ../neo
CC	= gcc
RM	= rm -fr

OUT	= test_address test_conn test_core test_date test_email test_fuzz \
	  test_hcache test_imap test_lib test_maildir test_mbox test_notmuch \
	  test_pattern test_sasl test_smtp

CFLAGS	+= -DDEBUG
CFLAGS	+= -Wall
CFLAGS	+= -Wno-unused-parameter
CFLAGS	+= -g
CFLAGS	+= -O0
CFLAGS	+= -I$(NEO)
CFLAGS	+= -fno-omit-frame-pointer

LDFLAGS	+= -L$(NEO)

# CFLAGS	+= -fsanitize=undefined -fno-sanitize-recover=undefined
# LDFLAGS	+= -fsanitize=undefined -fno-sanitize-recover=undefined

# CFLAGS	+=-fsanitize=address -fsanitize-recover=address
# LDFLAGS	+=-fsanitize=address -fsanitize-recover=address

# CFLAGS	+= -fsanitize=address -fno-sanitize-recover=address
# LDFLAGS	+= -fsanitize=address -fno-sanitize-recover=address

ADDR_LDFLAGS	= -laddress
COMPRESS_LDFLAGS= -lcompress
CONFIG_LDFLAGS	= -lconfig
CONN_LDFLAGS	= -lconn -lgnutls -lsasl2 -lanl
CORE_LDFLAGS	= -lcore
EMAIL_LDFLAGS	= -lemail
FUZZ_LDFLAGS	= -lemail
HCACHE_LDFLAGS	= -lhcache -lstore -ltokyocabinet -lkyotocabinet -lgdbm -lqdbm -ldb-5.3 -llmdb -lz -llz4 -lzstd -lrocksdb -ltdb
HISTORY_LDFLAGS	= -lhistory
IMAP_LDFLAGS	= -limap
MAILDIR_LDFLAGS	= -lmaildir -lstore -lpcre2-8
MBOX_LDFLAGS	= -lmbox
NOTMUCH_LDFLAGS	= $(NEO)/libnotmuch.a -lnotmuch -lz
MUTT_LDFLAGS	= -lmutt -lidn -lidn2 -lpcre2-8
PATTERN_LDFLAGS = $(NEO)/pattern.o -lpcre2-8
SEND_LDFLAGS	= -lsend

all:	$(NEO) $(OUT)

test_address: test_address.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_conn: test_conn.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(CONN_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_core: test_core.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(CORE_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(CONFIG_LDFLAGS) $(MUTT_LDFLAGS)

test_date: test_date.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(MUTT_LDFLAGS)

test_email: test_email.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_fuzz: test_fuzz.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(FUZZ_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_hcache: test_hcache.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(HCACHE_LDFLAGS) $(COMPRESS_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_imap: test_imap.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(MUTT_LDFLAGS)

test_lib: test_lib.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(MUTT_LDFLAGS) $(HISTORY_LDFLAGS)

test_maildir: test_maildir.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(MAILDIR_LDFLAGS) $(HCACHE_LDFLAGS) $(COMPRESS_LDFLAGS) $(CORE_LDFLAGS) $(CONFIG_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_mbox: test_mbox.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(MBOX_LDFLAGS) $(CORE_LDFLAGS) $(CONFIG_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_notmuch: test_notmuch.c
	$(CC) -o $@ $< $(CFLAGS) $(NEO)/libnotmuch.a $(NEO)/libhcache.a $(NEO)/libstore.a -ltokyocabinet -lkyotocabinet -lgdbm -lqdbm -ldb-5.3 -llmdb -lz -llz4 -lzstd $(NEO)/libnotmuch.a $(NEO)/libmaildir.a $(NEO)/libconfig.a $(NEO)/libcore.a $(NEO)/libcompress.a $(NEO)/libemail.a $(NEO)/libaddress.a $(NEO)/libmutt.a -lidn2 -lnotmuch -lpcre2-8 -lrocksdb -ltdb

test_pattern: test_pattern.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(PATTERN_LDFLAGS) $(CORE_LDFLAGS) $(CONFIG_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_sasl: test_sasl.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(CONN_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

test_smtp: test_smtp.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) $(SEND_LDFLAGS) $(CONN_LDFLAGS) $(CORE_LDFLAGS) $(CONFIG_LDFLAGS) $(EMAIL_LDFLAGS) $(ADDR_LDFLAGS) $(MUTT_LDFLAGS)

clean:
	$(RM) $(OUT) cache tmp

