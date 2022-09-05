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

SRC_DIR := ./src
OBJ_DIR := ./obj
include Makeincludes/asm.mk Makeincludes/asm.mk

include Makeincludes/libft.mk

.PHONY: all clean fclean re

all: $(LIBFT) $(ASM) $(COREWAR)

$(ASM): $(OBJ_DIR_ASM) $(OBJS_ASM)
	@$(CC) $(CFLAGS) $(OBJS_ASM) $(LIB_OBJS) $(LINK) -o $(@)

$(COREWAR): $(OBJ_DIR_COREWAR) $(OBJS_COREWAR)
	@$(CC) $(CFLAGS) $(OBJS_COREWAR) $(LIB_OBJS) $(LINK) -o $(@)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR) CFLAGS='$(CFLAGS)'
