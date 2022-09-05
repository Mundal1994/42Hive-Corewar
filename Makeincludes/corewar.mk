# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    corewar.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 13:34:21 by cchen             #+#    #+#              #
#    Updated: 2022/09/05 13:34:23 by cchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR_COREWAR := $(SRC_DIR)/corewar
SRCS_COREWAR := $(SRC_DIR_COREWAR)/op.c

OBJ_DIR_COREWAR := $(OBJ_DIR)/corewar
OBJS_COREWAR := $(SRCS_COREWAR:$(SRC_DIR_COREWAR)/%.c=$(OBJ_DIR_COREWAR)/%.o)
