#!/bin/bash

GIVEN_VM=$1
MY_VM=$2
CHAMP1=$3
CHAMP2=$4
END=0
COUNT=1


checking_lines()
{
	if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
	then
		printf "OK\n"
		exit 0
		#END=1
	elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
	then
		printf "KO\n"
		exit 0
	elif [[ "$line" != "$line2" ]]
	then
		END=1
	fi
}

while [[ END -eq 0 ]]
do
	$GIVEN_VM -d $COUNT $CHAMP1 $CHAMP2 > given_vm_dump$COUNT.txt
	$MY_VM -d $COUNT $CHAMP1 $CHAMP2 > vm_dump$COUNT.txt
	while read line
	do
		cat given_vm_dump$COUNT.txt
		while read line2
		do
			DOWN=1
			if [[ "$line" != "$line2" ]]
			then
				NEW=$(($COUNT - $DOWN))
				$GIVEN_VM -d $COUNT $CHAMP1 $CHAMP > given_vm_dump$NEW.txt
				$MY_VM -d $COUNT $CHAMP1 $CHAMP2 > vm_dump$NEW.txt
				END=1
				while  [[ END -eq 1 ]]
				do 
					END=0
					while read line
					do
						while read line2
						do
							
							if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
							then
								printf "OK\n"
								exit 0
								#END=1
							elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
							then
								printf "KO\n"
								exit 0
							elif [[ "$line" != "$line2" ]]
							then
								END=1
							fi
							# checking_lines()
							break
						done < vm_dump"$($COUNT - $DOWN)".txt
					done < given_vm_dump"$($COUNT - $DOWN)".txt
					if [[ END -eq 0 ]]
					then
						exit 0
					elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
					then
						printf "KO\n"
						exit 0
					else
					#then
						DOWN=$((DOWN+1))
						rm vm_dump$NEW.txt
						rm given_vm_dump$NEW.txt
					fi
				done
			fi
			if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
			then
				printf "OK\n"
				exit 0
				#END=1
			elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
			then
				printf "KO\n"
				exit 0
			fi
			#checking_lines()
			break
		done <vm_dump$COUNT.txt
	done <given_vm_dump$COUNT.txt
	rm vm_dump$COUNT.txt
	rm given_vm_dump$COUNT.txt
	COUNT=$((COUNT+50))
done