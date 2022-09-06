# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 13:16:36 by cchen             #+#    #+#              #
#    Updated: 2022/09/06 09:26:58 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM := asm
COREWAR := corewar
VM := vm

DIR := ./corewar
DIR_ASM := $(DIR)/$(ASM)
DIR_VM := $(DIR)/$(VM)

.PHONY: all clean fclean re

all: assembler vm

assembler:
	$(MAKE) -C ./$(DIR_ASM)
	mv ./$(DIR_ASM)/$(ASM) ./

vm:
	$(MAKE) -C ./$(DIR_VM)
	mv ./$(DIR_VM)/$(COREWAR) ./

clean:
	@$(MAKE) -C ./$(DIR_ASM) clean
	@$(MAKE) -C ./$(DIR_VM) clean

fclean:
	@$(MAKE) -C ./$(DIR_ASM) fclean
	@$(MAKE) -C ./$(DIR_VM) fclean
	rm $(ASM) $(VM)

re: fclean all
