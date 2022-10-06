#!/bin/zsh

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
DIR=$(dirname `which $0`)
cd $DIR

RUN_ASM () {
	echo "${YELLOW}Running our asm, & checking leaks${NC}"
	COR=$(echo $1 | sed 's/\.s/\.cor/g')
	leaks ../../asm $1
	leaks --atExit -- ../../asm $1 &> res
	if tail -n2 res | head -n1 | grep -q '0 leaks for 0 total leaked bytes.'; then
		echo "${GREEN}No leaks.${NC}"
	else
		echo "${RED}LEAKS!!!${NC}"
	fi
#	/bin/rm res
#	/bin/rm $COR
}

RUN_HIVE_ASM () {
	echo "${YELLOW}Running school asm${NC}"
	COR=$(echo $1 | sed 's/\.s/\.cor/g')
	HIVE=$(echo $1 | sed 's/\.s/\.hive/g')
	./hive_asm $1
	echo "Renaming: $COR -> $HIVE\n"
	/bin/mv $COR $HIVE
	/bin/rm $HIVE
}

echo "Testing valid maps..."
for f in $(find . -type f -name "*.s"); do
	echo $f
	RUN_HIVE_ASM $f
	RUN_ASM $f
	echo ""
done
