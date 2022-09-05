# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 22:53:20 by caruychen         #+#    #+#              #
#    Updated: 2022/09/05 23:08:59 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR := ../libft
LIB_OBJS = $(shell find $(LIB_DIR) -type f | grep -E "\.o$$")
LIB_INCLUDES := $(addprefix -I, $(shell find $(LIB_DIR)/includes -type d))

LIBFT := $(addprefix $(LIB_DIR), libft.a)
LINK := -L $(LIB_DIR) -lft
