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

TEST_INVALID () {
	echo $1
	../../asm $1 &> res
	ERR=$(grep 'Error' res)
	if [ "$ERR" != "" ]; then
		echo "${GREEN}ERROR reported${NC}"
	else
		echo "${RED}No ERROR reported${NC}"
	fi
	/bin/rm res
}

echo "Testing invalid maps...\n"
for f in $(find . -type f -name "*"); do
	TEST_INVALID $f
	LEAKS $f
	echo ""
done
