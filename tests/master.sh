#!/bin/zsh

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'

READ_CONT () {
	read -s -k "?Press any key to continue"
	echo ""
	tput cuu1
	tput el
}

RUN_CMD () {
	PROMPT=$1
	CMD=$2
	tput sc
	echo ${PROMPT}
	eval ${CMD}
	READ_YN
}

RET_YN () {
	while true
	do
		read -s -k "REPLY"
		if [ ${REPLY} = "y" ]
		then
			return true
		elif [ ${REPLY} = "n" ]
		then
			return false
		fi
	done
}

READ_YN () {
	if RET_YN false
	then
##		tput rc && tput cd
		echo "${GREEN}YES${NC}"
	else
#		tput rc && tput cd
		echo "${RED}NO${NC}"
	fi
}

NORM_MANUAL () {
	tput sc
	echo "${YELLOW}Would you like to see the norminette for yourself? [y/n]${NC}"
	while true
	do
		read -s -k "REPLY"
		if [ ${REPLY} = "y" ]
		then
			norminette ../
			echo "${YELLOW}Are you satisfied? [y/n]${NC}"
			if RET_YN
			then
				tput clear
				echo "- Evaluator is satisfied with the norme: ${GREEN}YES${NC}"
			else
				tput clear
				echo "- Evaluator is satisfied with the norme: ${RED}NO, BOOHOO${NC}"
			fi
			break
		elif [ ${REPLY} = "n" ]
		then
			tput rc && tput cd
			break
		fi
	done

}

NORMINETTE () {
	tput sc
	echo "${YELLOW}Auto-testing 'norminette ../'${NC}"
	res=$(norminette ../)
	tput rc && tput cd
	if echo ${res} | grep -q 'Error'
	then
		echo "${RED}NO${NC}"
	else
		echo "${GREEN}OK${NC}"
	fi
	NORM_MANUAL
}

tput clear
echo "Let's stop these mother@#$%in snakes on this mother@#$%in helltrain!\n"

echo "Welcome to the Corewar test, let's begin with the basics:"
READ_CONT

echo -n "- Something was submitted: "
RUN_CMD "\n${YELLOW}Running 'ls' from root, can you see stuff? [y/n]${NC}" "ls -al ../"
echo -n "- Author file repository: "
RUN_CMD "\n${YELLOW}Running 'ls' from root, can you see the author file? [y/n]${NC}" "ls -al ../"
echo -n "- Correct author file contents: "
RUN_CMD "\n${YELLOW}Printing author file with 'car -e', is if formatted correctly? [y/n]${NC}" "cat -e ../author"
echo -n "- Norm is OK: "
NORMINETTE
