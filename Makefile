# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 13:16:36 by cchen             #+#    #+#              #
#    Updated: 2022/09/05 13:19:36 by cchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM := asm
COREWAR := corewar

CC := gcc
CFLAGS := -Wall -Werror -Wextra
INCLUDES := -I./libft -I./includes

SRC := ./src
SRC_ASM := $(SRC)/asm
SRC_COREWAR := $(SRC)/corewar

.PHONY: all clean fclean re

all: $(ASM) $(COREWAR)
