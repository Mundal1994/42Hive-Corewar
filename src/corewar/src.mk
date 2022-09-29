# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 16:59:05 by caruychen         #+#    #+#              #
#    Updated: 2022/09/15 10:13:12 by cchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := ./src
SRCS := $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/op.c
SRCS += $(SRC_DIR)/init.c
SRCS += $(SRC_DIR)/read_init.c
SRCS += $(SRC_DIR)/game_start.c
SRCS += $(SRC_DIR)/update_carriages.c
SRCS += $(SRC_DIR)/print.c
SRCS += $(SRC_DIR)/statement.c