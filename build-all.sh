#!/bin/bash

VERSION=$1
PERSONAL="--prefix=/home/mutt/install"
COMMON="--enable-debug --enable-flock --enable-gpgme --enable-imap --enable-pop --enable-smtp --with-gnutls --with-gss --with-sasl --with-ssl --with-tokyocabinet"

if [[ "$VERSION" =~ mutt-([0-9]+)\.([0-9]+)\.([0-9]+) ]]; then
	VALUE=$(( (10000*${BASH_REMATCH[1]}) + (100*${BASH_REMATCH[2]}) + ${BASH_REMATCH[3]} ))
elif [[ "$VERSION" =~ neomutt-([0-9]{8}) ]]; then
	VALUE=${BASH_REMATCH[1]}
else
	echo "Don't understand version: '$VERSION'"
	exit 1
fi

if [ $VALUE -ge 20170414 ]; then
	OPTIONS="--disable-doc --disable-po --enable-compressed --enable-lua --enable-nntp --enable-notmuch --enable-sidebar --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm"
elif [ $VALUE -ge 20170113 ]; then
	OPTIONS="--disable-doc --disable-po --enable-compressed --enable-nntp --enable-notmuch --enable-sidebar --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm"
elif [ $VALUE -ge 20161126 ]; then
	OPTIONS="--disable-doc --disable-po --enable-compressed --enable-hcache --enable-nntp --enable-notmuch --enable-sidebar --with-bdb --with-gdbm --with-kyotocabinet --with-lmdb --with-qdbm"
elif [ $VALUE -ge 20161104 ]; then
	OPTIONS="--disable-doc --enable-compressed --enable-hcache --enable-nntp --enable-notmuch --enable-sidebar"
elif [ $VALUE -ge 20160530 ]; then
	OPTIONS="--enable-compressed --enable-hcache --enable-nntp --enable-notmuch --enable-sidebar"
elif [ $VALUE -ge 20160317 ]; then
	OPTIONS="--enable-hcache --enable-notmuch --enable-sidebar"
elif [ $VALUE -ge 20160307 ]; then
	OPTIONS="--enable-hcache --enable-sidebar"
elif [ $VALUE -ge 10800 ]; then
	OPTIONS="--disable-doc --enable-compressed --enable-hcache --enable-sidebar"
elif [ $VALUE -ge 10700 ]; then
	OPTIONS="--enable-hcache --enable-sidebar"
else
	OPTIONS="--enable-hcache"
fi

echo "$VERSION $OPTIONS"

