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
DIR_MK := $(patsubst %/Makefile, %, $(abspath $(lastword $(MAKEFILE_LIST))))

.PHONY: all clean fclean re asm corewar

all: $(ASM) $(COREWAR)

$(ASM):
	@$(MAKE) -C ./$(DIR_ASM) EXEC='$(DIR_MK)/$(@)'

$(COREWAR):
	@$(MAKE) -C ./$(DIR_COREWAR) EXEC='$(DIR_MK)/$(@)'

clean:
	@$(MAKE) -C ./$(DIR_ASM) clean
	@$(MAKE) -C ./$(DIR_COREWAR) clean

fclean:
	@$(MAKE) -C ./$(DIR_ASM) fclean EXEC='$(DIR_MK)/$(ASM)'
	@$(MAKE) -C ./$(DIR_COREWAR) fclean EXEC='$(DIR_MK)/$(COREWAR)'

re: fclean all

$(ASM)_debug:
	@$(MAKE) debug -C ./$(DIR_ASM) EXEC='$(DIR_MK)/$(ASM)'

$(COREWAR)_debug:
	@$(MAKE) debug -C ./$(DIR_COREWAR) EXEC='$(DIR_MK)/$(COREWAR)'

$(ASM)_fsan:
	@$(MAKE) fsan -C ./$(DIR_ASM) EXEC='$(DIR_MK)/$(ASM)'

$(COREWAR)_fsan:
	@$(MAKE) fsan -C ./$(DIR_COREWAR) EXEC='$(DIR_MK)/$(COREWAR)'
