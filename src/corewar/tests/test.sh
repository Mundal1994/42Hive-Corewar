#!/bin/bash

GIVEN_VM=./corewar
MY_VM=../corewar
CHAMP1=$1
CHAMP2=$2
CHAMP3=$3
CHAMP4=$4
OUTPUT="dump_test"
END=0

rm -fr dump_test
mkdir dump_test
if [[ "$GIVEN_VM" == "-h" ]]
then
	printf "usage:  arg1[absolute path 42 coreware vm]\n\
	arg2[absolute path your coreware vm]\n        arg3[absolute path champ1]\n        arg4[absolute path champ2]\n"
	exit 0
fi

drop_down()
{
	DOWN=1
	while [[ END -eq 0 ]]
	do
		if [[ DOWN -gt 50 ]]
		then
			break
		fi
		FLAG=0
		eof8=0
		eof9=0
		LINE_NBR=0
		$GIVEN_VM -d $((COUNT - DOWN)) $CHAMP1 $CHAMP2  $CHAMP3 $CHAMP4> dump_test/given_vm_dump$((COUNT - DOWN)).txt
		$MY_VM -dump $((COUNT - DOWN)) $CHAMP1 $CHAMP2  $CHAMP3 $CHAMP4> dump_test/vm_dump$((COUNT - DOWN)).txt
		exec 8<dump_test/given_vm_dump$((COUNT - DOWN)).txt
		exec 9<dump_test/vm_dump$((COUNT - DOWN)).txt
		while [[ $eof8 -eq 0  ||  $eof9 -eq 0 ]]
		do
			YES=$((YES+1))
			if read line <&8
			then
				LINE_NBR=$((LINE_NBR+1))
			else
				eof8=1
			fi
			if read line2 <&9
			then
				YES=0
			else
				eof9=1
			fi
			if [[ "$line" != "$line2" ]]
			then
			echo "$line"
			echo "$line2"
			printf "\n"
				FLAG=1
				HOLD=$line2
			fi
		done
		if [[ FLAG -eq 1 ]]
		then

			printf "KO [Difference at -d $((COUNT - DOWN + 1))]\nLINE\n$HOLD\n"
			exit 0
		fi
		rm dump_test/given_vm_dump$((COUNT - DOWN)).txt
		rm dump_test/vm_dump$((COUNT - DOWN)).txt
		DOWN=$((DOWN+1))
	done
}

drop_down_2()
{
	rm dump_test/vm_dump$COUNT.txt
	rm dump_test/given_vm_dump$COUNT.txt
	DOWN=1
	while [[ END -eq 0 ]]
	do
		FLAG=0
		eof5=0
		eof6=0
		LINE_NBR=0
		$GIVEN_VM -d $((COUNT - DOWN)) $CHAMP1 $CHAMP2  $CHAMP3 $CHAMP4> dump_test/given_vm_dump$((COUNT - DOWN)).txt
		$MY_VM -dump $((COUNT - DOWN)) $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> dump_test/vm_dump$((COUNT - DOWN)).txt
		exec 5<dump_test/given_vm_dump$((COUNT - DOWN)).txt
		exec 6<dump_test/vm_dump$((COUNT - DOWN)).txt
		while [[ $eof5 -eq 0  ||  $eof6 -eq 0 ]]
		do
			YES=$((YES+1))
			if read line <&5
			then
				LINE_NBR=$((LINE_NBR+1))
				YES=0
			else
				eof5=1
			fi
			if read line2 <&6
			then
				YES=0
			else
				eof6=1
			fi
			if  [[ "$line" != "$line2" ]]
			then
				HOLD=$LINE_NBR
			fi
		done
		if [[ FLAG -eq 1 ]]
		then
			echo "$line"
			echo "$line2"
			printf "KO  [Difference at -d $((COUNT - DOWN + 1))]\nLINE\n$HOLD\n"
			exit 0
		fi
		rm dump_test/given_vm_dump$((COUNT - DOWN)).txt
		rm dump_test/vm_dump$((COUNT - DOWN)).txt
		DOWN=$((DOWN+1))
		if [[ $DOWN -gt 50 ]]
		then
			break
		fi
	done
}

checking_lines()
{
	if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
	then
		echo "Ended together..."
		drop_down_2
		printf "Dump flag OK\n"
		rm -r dump_test
		exit 0
	elif [[ "$line" != "$line2" ]]
	then
		echo "Problem..."
		echo $line
		echo $line2
		drop_down
		exit 0
	fi
}

YES=0
$MY_VM -v 2 $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> dump_test/given_vm_dump.txt 
chmod 777 dump_test/given_vm_dump.txt
LEN=$(wc -l dump_test/given_vm_dump.txt | sed 's/[^0-9]*//g')
COUNT=$((LEN-500))
while [[ END -eq 0 ]]
do
	$GIVEN_VM -d $COUNT $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> dump_test/given_vm_dump$COUNT.txt
	$MY_VM -dump $COUNT $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4> dump_test/vm_dump$COUNT.txt
	eof3=0
	eof4=0
	exec 3<dump_test/given_vm_dump$COUNT.txt
	exec 4<dump_test/vm_dump$COUNT.txt
	while [[ $eof3 -eq 0  ||  $eof4 -eq 0 ]]
	do
		YES=$((YES+1))
		if read line <&3
		then
			YES=0
		else
			eof3=1
		fi
		if read line2 <&4
		then
			YES=0
		else
			eof4=1
		fi
		checking_lines
	done
	rm dump_test/vm_dump$COUNT.txt
	rm dump_test/given_vm_dump$COUNT.txt
	COUNT=$((COUNT+50))
done