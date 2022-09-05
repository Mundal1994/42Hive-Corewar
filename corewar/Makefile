# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 16:56:16 by caruychen         #+#    #+#              #
#    Updated: 2022/09/05 17:08:31 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := corewar

CC := gcc
CFLAGS := -Wall -Werror -Wextra
INCLUDES := -I../libft -I./includes

include src.mk

OBJ_DIR := ./obj
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIB_DIR := ../libft
LIBFT := $(addprefix $(LIB_DIR), libft.a)
LIB_OBJS = $(shell find $(LIB_DIR) -type f | grep -E "\.o$$")
LINK := -L ./libft -lft

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_OBJS) $(LINK) -o $(@)

$(OBJ_DIR):
	@mkdir -p $(@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR) CFLAGS='$(CFLAGS)'

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
