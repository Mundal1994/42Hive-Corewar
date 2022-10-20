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

READ_YN () {
	read -s -k "REPLY"
	if [ ${REPLY} = "y" ]
	then
		tput rc
		tput el
	else
		echo ${REPLY}
	fi
}

echo "Let's stop these mother@#$%in snakes on this mother@#$%in helltrain!\n"

echo "Welcome to the Corewar test, let's begin with the basics:"
READ_CONT

echo "- Something was submitted: ${GREEN}YES${NC}"
echo -n "- Author file repository: "
RUN_CMD "\n${YELLOW}Running 'ls' from root, can you see the author file? [y/n]${NC}" "ls -al ../"
