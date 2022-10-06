#!/bin/zsh

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
DIR=$(dirname `which $0`)
cd $DIR

LEAKS () {
	leaks --atExit -- ../../asm $1 &> res
	if tail -n2 res | head -n1 | grep -q '0 leaks for 0 total leaked bytes.'; then
		echo "${GREEN}No leaks.${NC}"
	else
		echo "${RED}LEAKS!!!${NC}"
	fi
	/bin/rm res
}

RUN_HIVE_ASM () {
	echo $1
	./hive_asm $1
	rm $1
}

echo "Testing valid maps..."
for f in $(find . -type f -name "*.s"); do
	RUN_HIVE_ASM $f
	echo ""
done
