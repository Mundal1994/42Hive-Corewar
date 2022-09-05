# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asm.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 13:34:29 by cchen             #+#    #+#              #
#    Updated: 2022/09/05 13:34:30 by cchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR_ASM := $(SRC_DIR)/asm
SRCS_ASM := $(SRC_DIR_ASM)/main.c

OBJ_DIR_ASM := $(OBJ_DIR)/asm
OBJS_ASM := $(SRCS_ASM:$(SRC_DIR_ASM)/%.c=$(OBJ_DIR_ASM)/%.o)
