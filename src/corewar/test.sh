#!/bin/bash

GIVEN_VM=$1
MY_VM=$2
CHAMP1=$3
CHAMP2=$4
END=0
COUNT=1

if [[ "$GIVEN_VM" == "-h" ]]
then
	printf "usage:  arg1[absolute path 42 coreware vm]\n\
	arg2[absolute path your coreware vm]\n        arg3[absolute path champ1]\n        arg4[absolute path champ2]\n"
	exit 0
fi

drop_down()
{
	rm vm_dump$COUNT.txt
	rm given_vm_dump$COUNT.txt
	DOWN=1
	while [[ END -eq 0 ]]
	do
		FLAG=0
		eof5=0
		eof6=0
		LINE_NBR=0
		#printf "$COUNT   $DOWN\n"
		$GIVEN_VM -d $((COUNT - DOWN)) $CHAMP1 $CHAMP2 > given_vm_dump$((COUNT - DOWN)).txt
		$MY_VM -d $((COUNT - DOWN)) $CHAMP1 $CHAMP2 > vm_dump$((COUNT - DOWN)).txt
		exec 5<given_vm_dump$((COUNT - DOWN)).txt
		exec 6<vm_dump$((COUNT - DOWN)).txt
		while [[ $eof5 -eq 0  ||  $eof6 -eq 0 ]]
		do
			YES=$((YES+1))
			if read line <&5
			then
				LINE_NBR=$((LINE_NBR+1))
			else
				eof5=1
			fi
			if read line2 <&6
			then
				YES=0
			else
				eof6=1
			fi
			# printf "LIL $((COUNT-DOWN))\n"
			# echo "$line"
			# echo "$line2"
			#exit 0
			if [[ "$line" != "$line2" ]]
			then
			echo "$line"
			echo "$line2"
			printf "\n"
				FLAG=1
				HOLD=$line2
			fi
		done
		#printf "END $DOWN\n"
		if [[ FLAG -eq 0 ]]
		then

			printf "KO [Difference at -d $((COUNT - DOWN + 1))]\nLINE\n$HOLD\n"
			exit 0
		fi
		rm given_vm_dump$((COUNT - DOWN)).txt
		rm vm_dump$((COUNT - DOWN)).txt
		DOWN=$((DOWN+1))
	done
}

drop_down_2()
{
	rm vm_dump$COUNT.txt
	rm given_vm_dump$COUNT.txt
	DOWN=1
	while [[ END -eq 0 ]]
	do
		FLAG=0
		eof5=0
		eof6=0
		LINE_NBR=0
		$GIVEN_VM -d $((COUNT - DOWN)) $CHAMP1 $CHAMP2 > given_vm_dump$((COUNT - DOWN)).txt
		$MY_VM -d $((COUNT - DOWN)) $CHAMP1 $CHAMP2 > vm_dump$((COUNT - DOWN)).txt
		exec 5<given_vm_dump$((COUNT - DOWN)).txt
		exec 6<vm_dump$((COUNT - DOWN)).txt
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
			#printf "LIL $((COUNT-DOWN))\n"
			#echo "$line"
			#echo "$line2"
			#exit 0
			if [[ "$line" == *"has won"*  &&  "$line2" != *"has won"* ]]
			then
				drop_down
			elif [[ "$line2" == *"has won"*  &&  "$line" != *"has won"* ]]
			then
				drop_down
			elif  [[ "$line" != "$line2" ]]
			then
				FLAG=1
				HOLD=$LINE_NBR
			fi
		done
		#printf "END $DOWN\n"
		if [[ FLAG -eq 1 ]]
		then

			printf "KO  [Difference at -d $((COUNT - DOWN + 1))]\nLINE\n$HOLD\n"
			exit 0
		fi
		rm given_vm_dump$((COUNT - DOWN)).txt
		rm vm_dump$((COUNT - DOWN)).txt
		DOWN=$((DOWN+1))
		if [[ $DOWN -eq 50 ]]
		then
			break
		fi
	done
}

checking_lines()
{
	if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
	then
		#printf "HERE\n"
		drop_down_2
		printf "OK\n"
		exit 0
	# elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
	# then
	# 	if [[ "$line" == *"has won"* ]]
	# 	then
	# 		printf "KO   [42_vm ended]\n"
	# 	elif [[ "$line2" == *"has won"* ]]
	# 	then
	# 		printf "KO   [our vm ended]\n"
	# 	fi
	# 	exit 0
	elif [[ "$line" != "$line2" ]]
	then
		# echo $line
		# echo $line2
		#printf "problem\n"
		drop_down
		exit 0
	fi
}

YES=0

while [[ END -eq 0 ]]
do
	$GIVEN_VM -d $COUNT $CHAMP1 $CHAMP2 > given_vm_dump$COUNT.txt
	$MY_VM -d $COUNT $CHAMP1 $CHAMP2 > vm_dump$COUNT.txt
	eof3=0
	eof4=0
	exec 3<given_vm_dump$COUNT.txt
	exec 4<vm_dump$COUNT.txt
	#printf "$COUNT\n"
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
		# printf "BIG $COUNT\n"
		#echo "$line"
		#echo "$line2"
		checking_lines
	done
	#echo "end"
	rm vm_dump$COUNT.txt
	rm given_vm_dump$COUNT.txt
	COUNT=$((COUNT+50))
done