#!/bin/bash

declare -ir MAX_SECONDS=3600
declare -ir TIMEOUT=$SECONDS+$MAX_SECONDS
ELEMENTS_IN_DIR=$(ls test_champs/ | wc -l)

find_champ () {
	limit=$(($RANDOM % $ELEMENTS_IN_DIR + 1))
	i=0
	for filename in test_champs/*; do
		((i++))
		if [ $i -eq $limit ]; then
			eval "$1=$filename"
			break
		fi
	done
}

while (( $SECONDS < $TIMEOUT )); do
	CHAMP1=''
	find_champ CHAMP1
	CHAMP2=''
	find_champ CHAMP2
	CHAMP3=''
	find_champ CHAMP3
	CHAMP4=''
	find_champ CHAMP4
	echo "CHAMPIONS SELECTED: $CHAMP1, $CHAMP2, $CHAMP3 & $CHAMP4"
	./test_v_flag.sh $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4
done