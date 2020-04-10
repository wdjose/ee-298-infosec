#!/bin/bash

for var in "$@"
do
	echo "du -b $var"
	du -b $var
	echo
	echo "sha512sum $var"
	(time sha512sum $var | head -n1 | awk '{print $1;}') 2>&1
	echo
	echo "python file_sha512.py $var"
	(time python file_sha512.py $var) 2>&1
	echo
	echo "./file_sha512.out $var"
	(time ./file_sha512.out $var) 2>&1
	echo
	echo
done
