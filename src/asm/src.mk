# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 17:20:05 by caruychen         #+#    #+#              #
#    Updated: 2022/10/03 22:04:39 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := ./src
SRCS := $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/validator.c
SRCS += $(SRC_DIR)/source.c
SRCS += $(SRC_DIR)/source_line.c
SRCS += $(SRC_DIR)/source_read.c
SRCS += $(SRC_DIR)/symbol.c
SRCS += $(SRC_DIR)/assemble.c
SRCS += $(SRC_DIR)/lexer.c
SRCS += $(SRC_DIR)/lexer_bools.c
SRCS += $(SRC_DIR)/lexer_getchar.c
SRCS += $(SRC_DIR)/lexer_getcmd.c
SRCS += $(SRC_DIR)/lexer_getcomment.c
SRCS += $(SRC_DIR)/lexer_getdirect.c
SRCS += $(SRC_DIR)/lexer_getnumber.c
SRCS += $(SRC_DIR)/lexer_getquote.c
SRCS += $(SRC_DIR)/lexer_getreference.c
SRCS += $(SRC_DIR)/lexer_getword.c
SRCS += $(SRC_DIR)/lexer_next.c
SRCS += $(SRC_DIR)/symtable.c
SRCS += $(SRC_DIR)/symtable_enter.c
SRCS += $(SRC_DIR)/parse.c
SRCS += $(SRC_DIR)/parse_header.c
SRCS += $(SRC_DIR)/parse_body.c
SRCS += $(SRC_DIR)/parse_operation.c
SRCS += $(SRC_DIR)/parse_register.c
SRCS += $(SRC_DIR)/parse_direct.c
SRCS += $(SRC_DIR)/parse_indirect.c
SRCS += $(SRC_DIR)/parse_reference.c
SRCS += $(SRC_DIR)/parse_numeric.c
SRCS += $(SRC_DIR)/parse_arg_end.c
SRCS += $(SRC_DIR)/opmap.c
SRCS += $(SRC_DIR)/errors.c
SRCS += $(SRC_DIR)/errors_exit.c
