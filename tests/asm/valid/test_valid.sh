#!/bin/zsh

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
DIR=$(dirname `which $0`)
cd $DIR

if [ $# -eq 0 ]
then
	echo "${RED}Hive asm executable required!${NC}"
	exit 1
fi

HIVE_ASM=$1

CHECK_LEAKS () {
	echo -n "Leaks: "
	leaks --atExit -- ../../../asm $1 &> res
	if tail -n2 res | head -n1 | grep -q '0 leaks for 0 total leaked bytes.'; then
		echo "${GREEN}No leaks.${NC}"
	else
		echo "${RED}LEAKS!!!${NC}"
		exit 1
	fi
	/bin/rm res
	/bin/rm $2
}

RUN_ASM () {
	echo "Running our asm:"
	CHECK_LEAKS $1 $2
	../../../asm $1
	echo ""
}

RUN_HIVE_ASM () {
	echo "Running school asm:"
	./$HIVE_ASM $1
	echo "Renaming: $2 -> $3\n"
	/bin/mv $2 $3
}

COMPARE () {
	COR=$1
	HIVE=$2
	DIFF_FILE=$(echo $1 | sed 's/\.cor/\.diff/g')
	echo "Running comparison:"
	hexdump -vC $COR > dumpcor
	hexdump -vC $HIVE > dumphive
	DIFF=$(diff dumpcor dumphive)
	if [ "$DIFF" != "" ]
	then
		echo "${RED}Found a difference${NC}"
		echo $DIFF > $DIFF_FILE
		exit 1
	else
		echo "${GREEN}Outputs identical${NC}"
		/bin/rm $COR $HIVE
	fi
	/bin/rm dumpcor dumphive
}

if [[ -f "../../../asm" ]]
then
	echo "${YELLOW}Testing valid maps...${NC}"
else
	echo "${RED}Missing asm executable!${NC}"
	exit 1
fi

rm -f files/*.diff 2> /dev/null
echo ""

for f in $(find . -type f -name "*.s"); do
	echo "${YELLOW}$f${NC}"
	COR=$(echo $f | sed 's/\.s/\.cor/g')
	HIVE=$(echo $f | sed 's/\.s/\.hive/g')
	RUN_HIVE_ASM $f $COR $HIVE
	RUN_ASM $f $COR
	COMPARE $COR $HIVE
	echo ""
done
