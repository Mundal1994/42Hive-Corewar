# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 17:20:05 by caruychen         #+#    #+#              #
#    Updated: 2022/09/23 11:28:41 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := ./src
SRCS := $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/validator.c
SRCS += $(SRC_DIR)/io_read.c
SRCS += $(SRC_DIR)/source.c
SRCS += $(SRC_DIR)/ast.c
SRCS += $(SRC_DIR)/lexer.c
SRCS += $(SRC_DIR)/opmap.c
SRCS += $(SRC_DIR)/parse.c
SRCS += $(SRC_DIR)/parse_header.c
SRCS += $(SRC_DIR)/cleanup.c
