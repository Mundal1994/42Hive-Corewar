#!/bin/zsh

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
DIR=$(dirname `which $0`)
cd $DIR

for f in $(find . -type f -name "*"); do
	echo "$f"
	../asm $f
	echo ""
done

rm valid/files/*.cor
rm bonus/*.cor
