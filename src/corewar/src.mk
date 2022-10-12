# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 16:59:05 by caruychen         #+#    #+#              #
#    Updated: 2022/10/12 12:35:15 by jdavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := ./src
SRCS := $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/op.c
SRCS += $(SRC_DIR)/init.c
SRCS += $(SRC_DIR)/read_init.c
SRCS += $(SRC_DIR)/game_start.c
SRCS += $(SRC_DIR)/update_carriages.c
SRCS += $(SRC_DIR)/check.c
SRCS += $(SRC_DIR)/print.c
SRCS += $(SRC_DIR)/statement.c
SRCS += $(SRC_DIR)/statement_bit.c
SRCS += $(SRC_DIR)/statement_more.c
SRCS += $(SRC_DIR)/statement_no_truncate.c
SRCS += $(SRC_DIR)/move.c
SRCS += $(SRC_DIR)/read_args_core.c
SRCS += $(SRC_DIR)/error.c