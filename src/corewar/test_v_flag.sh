#!/bin/bash

GIVEN_VM=../../../vm_champs/corewar
MY_VM=./corewar
CHAMP1=$1
CHAMP2=$2
CHAMP3=$3
CHAMP4=$4
flag=1
END=0
COUNT=0
FILE1=v_flags_results/given_vm.txt
FILE2=v_flags_results/vm.txt

rm -fr v_flags_results
mkdir v_flags_results
while [[ flag -lt 25 ]]
do
	$GIVEN_VM -v $flag $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> $FILE1
	$MY_VM -v $flag $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> $FILE2

	eof3=0
	eof4=0
	exec 3<$FILE1
	exec 4<$FILE2

	while [[ $eof3 -eq 0  ||  $eof4 -eq 0 ]]
	do
		COUNT=$((COUNT+1))
		YES=$((YES+1))
		if read line <&3
		then
			# while [[ "$line" != *"P"* ]]
			# do
			#	 if read line <&3
			#	 then
			#		 YES=0
			#	 else
			#		 eof3=1
			#	 fi
			# done
			YES=0
		else
			eof3=1
		fi
		if read line2 <&4
		then
			# while [[ "$line2" != *"P"* ]]
			# do
			#	 COUNT=$((COUNT+1))
			#	 if read line2 <&4
			#	 then
			#		 YES=0
			#	 else
			#		 eof3=1
			#	 fi
			# done
			YES=0
		else
			eof4=1
		fi
		if [[ "$line" != "$line2" ]]
		then
			printf "ERROR on line $COUNT of $FILE2, flag $flag\n"
			echo $line
			echo $line2
			printf "\n"
			break
		fi
	done
	printf "flag $flag OK\n"
	rm $FILE1
	rm $FILE2
	flag=$((flag+1))
done