# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 13:16:36 by cchen             #+#    #+#              #
#    Updated: 2022/09/15 10:16:56 by cchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM := asm
COREWAR := corewar

DIR := ./src
DIR_ASM := $(DIR)/$(ASM)
DIR_COREWAR := $(DIR)/$(COREWAR)

.PHONY: all clean fclean re

all: assembler corewar

assembler:
	@$(MAKE) -C ./$(DIR_ASM)
	@mv $(DIR_ASM)/$(ASM) ./

corewar:
	@$(MAKE) -C ./$(DIR_COREWAR)
	@mv $(DIR_COREWAR)/$(COREWAR) ./

clean:
	@$(MAKE) -C ./$(DIR_ASM) clean
	@$(MAKE) -C ./$(DIR_COREWAR) clean

fclean:
	@$(MAKE) -C ./$(DIR_ASM) fclean
	@$(MAKE) -C ./$(DIR_COREWAR) fclean
	rm $(ASM) $(COREWAR)

re: fclean all
