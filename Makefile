# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 13:16:36 by cchen             #+#    #+#              #
#    Updated: 2022/09/06 09:13:06 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM := asm
VM := corewar

ASM_DIR := corewar_asm
VM_DIR := corewar_vm

.PHONY: all clean fclean re

all: assembler vm

assembler:
	$(MAKE) -C ./$(ASM_DIR)
	mv ./$(ASM_DIR)/$(ASM) ./

vm:
	$(MAKE) -C ./$(VM_DIR)
	mv ./$(VM_DIR)/$(VM) ./

clean:
	@$(MAKE) -C ./$(ASM_DIR) clean
	@$(MAKE) -C ./$(VM_DIR) clean

fclean:
	@$(MAKE) -C ./$(ASM_DIR) fclean
	@$(MAKE) -C ./$(VM_DIR) fclean
	rm $(ASM) $(VM)

re: fclean all
