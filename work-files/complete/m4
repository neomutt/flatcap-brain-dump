NEO	?= ../neo
CC	= gcc
RM	= rm -fr

OUT	= demo

SRC	+= main.c account.c mailbox.c neomutt.c
SRC	+= config/address.c config/bool.c config/dump.c config/enum.c config/long.c config/mbtable.c config/regex.c config/number.c config/quad.c config/set.c config/slist.c config/sort.c config/string.c config/subset.c
SRC	+= test/common.c test/account.c test/address.c test/bool.c test/deep.c test/enum.c test/inherit.c test/initial.c test/long.c test/mbtable.c test/number.c test/quad.c test/regex.c test/set.c test/slist.c test/sort.c test/string.c test/synonym.c
SRC	+= dump/dump.c dump/data.c dump/vars.c

OBJ	+= $(SRC:%.c=%.o)

CFLAGS	+= -std=c99
CFLAGS	+= -Wall
# CFLAGS	+= -Wextra
# CFLAGS	+= -Wno-missing-field-initializers
# CFLAGS	+= -Wno-unused-parameter
# CFLAGS	+= -Wno-sign-compare
CFLAGS	+= -Wpedantic
CFLAGS	+= -ggdb3
CFLAGS	+= -O0
CFLAGS	+= -I.
CFLAGS	+= -I$(NEO)
CFLAGS	+= -D_GNU_SOURCE
# CFLAGS	+= -fprofile-arcs -ftest-coverage
# CFLAGS	+= -fsanitize=address
# CFLAGS	+= -fsanitize-recover=address

LDFLAGS	+= -L$(NEO)
LDFLAGS += -lemail
LDFLAGS += -laddress
LDFLAGS += -lmutt
LDFLAGS += -lidn
LDFLAGS += -lidn2
LDFLAGS	+= -pthread
LDFLAGS	+= -rdynamic
LDFLAGS	+= -fprofile-arcs -ftest-coverage
# LDFLAGS	+= -fsanitize=address
# LDFLAGS	+= -fsanitize-recover=address

CFLAGS	+= -fno-omit-frame-pointer

all:	$(OBJ) $(OUT) tags

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT):	$(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

test:	$(OUT) force
	-./$(OUT) set     > test/set.txt
	-./$(OUT) account > test/account.txt
	-./$(OUT) initial > test/initial.txt
	-./$(OUT) synonym > test/synonym.txt
	-./$(OUT) address > test/address.txt
	-./$(OUT) bool    > test/bool.txt
	-./$(OUT) enum    > test/enum.txt
	-./$(OUT) long    > test/long.txt
	-./$(OUT) mbtable > test/mbtable.txt
	-./$(OUT) number  > test/number.txt
	-./$(OUT) quad    > test/quad.txt
	-./$(OUT) regex   > test/regex.txt
	-./$(OUT) slist   > test/slist.txt
	-./$(OUT) sort    > test/sort.txt
	-./$(OUT) string  > test/string.txt
	-./$(OUT) deep    > test/deep.txt
	-./$(OUT) dump    > dump/dump.txt

tags:	$(SRC) $(HDR) force
	ctags -R .

clean:
	$(RM) $(OUT) $(OBJ)

distclean: clean
	$(RM) tags
	$(RM) *.gc?? */*.gc??
	$(RM) lcov.info lcov

force:

dummy_dirs:
	(cd config && rm -f config && ln -s . config)
	(cd mutt   && rm -f mutt   && ln -s . mutt)
	(cd test   && rm -f test   && ln -s . test)

coveralls: dummy_dirs all test force
	coveralls -e mutt -e test -e dump -e main.c -e config/dump.c

lcov: all test force
	$(RM) lcov
	$(RM) main.gc?? test/*.gc?? mutt/*.gc?? config/dump.gc??
	lcov -t "result" -o lcov.info -c -d config
	genhtml -o lcov lcov.info
	realpath lcov/config/index-sort-l.html

