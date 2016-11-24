#!/bin/bash

# set -o errexit	# set -e
# set -o nounset	# set -u

function log_error()
{
	echo -e "\e[1;31m$@\e[m"
}

function log_success()
{
	echo -e "\e[1;32m$@\e[m"
}

function die()
{
	if [ $? = 1 ]; then
		log_error "Build failed"
	fi
}


trap die EXIT

DIR="neo"

COMPILERS=(
	gcc
	# clang
)

COMMON_OPTIONS="--enable-pop --enable-imap --enable-smtp --enable-gpgme --enable-sidebar --enable-nntp --enable-notmuch --enable-compressed --enable-flock --enable-debug --with-gnutls --with-sasl --with-gss --disable-doc --disable-po"
OPTIONS=(
	""

	"--enable-hcache --with-bdb"
	"--enable-hcache --with-gdbm"
	"--enable-hcache --with-kyotocabinet"
	"--enable-hcache --with-lmdb"
	"--enable-hcache --with-qdbm"
	"--enable-hcache --with-tokyocabinet"

	"--enable-hcache --with-bdb --with-gdbm"
	"--enable-hcache --with-bdb --with-kyotocabinet"
	"--enable-hcache --with-bdb --with-lmdb"
	"--enable-hcache --with-bdb --with-qdbm"
	"--enable-hcache --with-bdb --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-kyotocabinet"
	"--enable-hcache --with-gdbm --with-lmdb"
	"--enable-hcache --with-gdbm --with-qdbm"
	"--enable-hcache --with-gdbm --with-tokyocabinet"
	"--enable-hcache --with-kyotocabinet --with-lmdb"
	"--enable-hcache --with-kyotocabinet --with-qdbm"
	"--enable-hcache --with-kyotocabinet --with-tokyocabinet"
	"--enable-hcache --with-lmdb --with-qdbm"
	"--enable-hcache --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-qdbm --with-tokyocabinet"

	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet"
	"--enable-hcache --with-bdb --with-gdbm --with-lmdb"
	"--enable-hcache --with-bdb --with-gdbm --with-qdbm"
	"--enable-hcache --with-bdb --with-gdbm --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-lmdb"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-qdbm"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-lmdb --with-qdbm"
	"--enable-hcache --with-bdb --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-lmdb"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-qdbm"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-lmdb --with-qdbm"
	"--enable-hcache --with-gdbm --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-kyotocabinet --with-lmdb --with-qdbm"
	"--enable-hcache --with-kyotocabinet --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-kyotocabinet --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-lmdb --with-qdbm --with-tokyocabinet"

	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb"
	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-qdbm"
	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-gdbm --with-lmdb --with-qdbm"
	"--enable-hcache --with-bdb --with-gdbm --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-gdbm --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-lmdb --with-qdbm"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-lmdb --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-lmdb --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-kyotocabinet --with-lmdb --with-qdbm --with-tokyocabinet"

	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm"
	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-gdbm --with-lmdb --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-bdb --with-kyotocabinet --with-lmdb --with-qdbm --with-tokyocabinet"
	"--enable-hcache --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm --with-tokyocabinet"

	"--enable-hcache --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm --with-tokyocabinet"
)


TOTAL=$((${#COMPILERS[@]} * ${#OPTIONS[@]}))
echo "Testing $TOTAL configurations"

pushd "$DIR" >& /dev/null

COUNT=1
SUCCESS=0
for c in "${COMPILERS[@]}"; do
	for o in "${OPTIONS[@]}"; do
		NAME=${o#--enable-hcache}
		NAME=${NAME// /}
		NAME=${NAME//--with/}

		echo "------------------------------------------------------------------------------"
		echo -e "\e[1;36mBuild $COUNT of $TOTAL\e[m -- $(date '+%F %R:%S')"
		echo -e "\e[1m./configure $o\e[m"
		echo
		git clean -xdfq
		autoreconf --install >& /dev/null
		./configure --quiet --disable-dependency-tracking $COMMON_OPTIONS $o CC="$c" CFLAGS="-g -Wall -O0 -fno-delete-null-pointer-checks"
		sed -i 's/\<cru\>/cr/' imap/Makefile
		if make -s; then
			log_success "Build succeeded"
			: $((SUCCESS++))
			cp --backup=t mutt ../mutt$NAME
		else
			log_error "Build failed"
		fi
		: $((COUNT++))
	done
done

: $((COUNT--))

git clean -xdfq
popd >& /dev/null

if [ $SUCCESS = $COUNT ]; then
	log_success "Success: $SUCCESS/$COUNT builds succeeded"
else
	log_error "Only: $SUCCESS/$COUNT builds succeeded"
fi
date

