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

YES=0
eof3=0
eof4=0
while [[ END -eq 0 ]]
do
	$GIVEN_VM -d $COUNT $CHAMP1 $CHAMP2 > given_vm_dump$COUNT.txt
	$MY_VM -d $COUNT $CHAMP1 $CHAMP2 > vm_dump$COUNT.txt
	# while read line
	# do
	# 	#cat vm_dump$COUNT.txt
	# 	while read line2
	# 	do
			exec 3<given_vm_dump$COUNT.txt
			exec 4<vm_dump$COUNT.txt
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
				printf "BIG\n"
				echo "$line"
				echo "$line2"
				DOWN=1
				# if [[ "$line" != "$line2" ]]
				# then
				# 	NEW=$(($COUNT - $DOWN))
				# 	$GIVEN_VM -d $COUNT $CHAMP1 $CHAMP > given_vm_dump$NEW.txt
				# 	$MY_VM -d $COUNT $CHAMP1 $CHAMP2 > vm_dump$NEW.txt
				# 	exec 7<given_vm_dump$NEW.txt
				# 	exec 8<vm_dump$NEW.txt
				# 	END=1
				# 	while  [[ END -eq 1 ]]
				# 	do 
				# 		printf "LITTE\n"
				# 		END=0
				# 		# while read line
				# 		# do
				# 		# 	while read line2
				# 		# 	do
				# 				read line <&7
				# 				read line2 <&8
				# 				echo $line
				# 				echo $line2
				# 				exit 0
				# 				if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
				# 				then
				# 					printf "OK\n"
				# 					exit 0
				# 					#END=1
				# 				elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
				# 				then
				# 					printf "KO\n"
				# 					exit 0
				# 				elif [[ "$line" != "$line2" ]]
				# 				then
				# 					END=1
				# 				fi
				# 				# checking_lines()
				# 		# 		break
				# 		# 	done < vm_dump$NEW.txt
				# 		# done < given_vm_dump$NEW.txt
				# 		if [[ END -eq 0 ]]
				# 		then
				# 			exit 0
				# 		elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
				# 		then
				# 			printf "KO\n"
				# 			exit 0
				# 		else
				# 		#then
				# 			DOWN=$((DOWN+1))
				# 			rm vm_dump$NEW.txt
				# 			rm given_vm_dump$NEW.txt
				# 		fi
				# 	done
				# fi
				# if [[ "$line" == *"has won"* && "$line2" == *"has won"* ]]
				# then
				# 	printf "OK\n"
				# 	exit 0
				# 	#END=1
				# elif [[ "$line" == *"has won"* || "$line2" == *"has won"* ]]
				# then
				# 	printf "KO\n"
				# 	exit 0
				# fi
			done
			#checking_lines()
	# 		break
	# 	done <vm_dump$COUNT.txt
	# done <given_vm_dump$COUNT.txt
	rm vm_dump$COUNT.txt
	rm given_vm_dump$COUNT.txt
	COUNT=$((COUNT+50))
done