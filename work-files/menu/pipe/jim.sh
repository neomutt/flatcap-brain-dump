#!/bin/bash

TMP_FILE=$(mktemp)

cat > "$TMP_FILE"

file "$TMP_FILE"

echo $# args
for i in "${@}"; do
	echo ">>$i<<"
done

