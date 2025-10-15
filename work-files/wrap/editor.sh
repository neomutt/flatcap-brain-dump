#!/bin/bash

for i in {001..050}; do
	NUM=$(((RANDOM%50)+1))
	echo "L${i} $(shuf -n $NUM /usr/share/dict/words | paste -s -d' ') L${i}"
done

