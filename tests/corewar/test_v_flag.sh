#!/bin/bash

GIVEN_VM=./corewar
MY_VM=../../corewar
CHAMP1=$1
CHAMP2=$2
CHAMP3=$3
CHAMP4=$4
flag=1
END=0
FILE1=v_flags_results_test/given_vm.txt
FILE2=v_flags_results_test/vm.txt

rm -fr v_flags_results_test
mkdir v_flags_results_test
while [[ flag -lt 25 ]]
do
	$GIVEN_VM -v $flag $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> $FILE1
	$MY_VM -v $flag $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> $FILE2

	eof10=0
	eof11=0
	exec 10<$FILE1
	exec 11<$FILE2
	COUNT=0
	ERROR=0
	while [[ $eof10 -eq 0  ||  $eof11 -eq 0 ]]
	do
		COUNT=$((COUNT+1))
		YES=$((YES+1))
		if read line <&10
		then
			YES=0
		else
			eof10=1
		fi
		if read line2 <&11
		then
			YES=0
		else
			eof11=1
		fi
		if [[ "$line" != "$line2" ]]
		then
			printf "flag $flag ERROR\n"
			printf "line $COUNT of $FILE2, flag $flag\n"
			echo $line
			echo $line2
			printf "\n"
			ERROR=1
			break
		fi
	done
	if [[ ERROR -eq 0 ]]
	then
		printf "flag $flag OK\n"
	fi
	rm $FILE1
	rm $FILE2
	exec 10>&-
	exec 11>&-
	flag=$((flag+1))
done
rm -r v_flags_results_test
./test.sh $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4
