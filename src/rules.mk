# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rules.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 09:57:02 by caruychen         #+#    #+#              #
#    Updated: 2022/09/07 10:29:05 by caruychen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
############################### Compiler flags #################################
################################################################################
CC := gcc
CFLAGS := -Wall -Werror -Wextra

################################################################################
############################### Object variables ###############################
################################################################################
OBJ_DIR := ./obj
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP_DIR := dep

################################################################################
############################### Libft variables ################################
################################################################################
LIB_DIR := ../../libft
LIB_OBJS = $(shell find $(LIB_DIR) -type f | grep -E "\.o$$")
LIBFT := $(addprefix $(LIB_DIR), libft.a)

################################################################################
########################### Include & Link variables ###########################
################################################################################
INCLUDES := $(addprefix -I, $(shell find $(LIB_DIR)/includes -type d)) \
		-I./includes -I../shared/includes
LINK := -L $(LIB_DIR) -lft

################################################################################
############################### Rules & Recipes ################################
################################################################################
.PHONY: all clean fclean re

all: $(LIBFT) $(EXEC)

-include $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

$(EXEC): $(DEP_DIR) $(OBJ_DIR) $(OBJS)
	@echo "Compiling $(EXEC)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_OBJS) $(LINK) -o $(@)

$(OBJ_DIR):
	@mkdir -p $(@)

$(DEP_DIR):
	@mkdir -p $(@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<
	@set -e; rm -f $(DEP_DIR)/$*.d; \
	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $(DEP_DIR)/$*.d.$$$$; \
	sed 's,\($*\)\.o[ :]*,$@ $(DEP_DIR)/\1.d : ,g' < $(DEP_DIR)/$*.d.$$$$ > $(DEP_DIR)/$*.d; \
	rm -f $(DEP_DIR)/$*.d.$$$$

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR) CFLAGS='$(CFLAGS)'

debug: CFLAGS += -g
debug: clean $(LIBFT) $(EXEC)

fsan: CFLAGS += -fsanitize=address -g
fsan: clean $(LIBFT) $(EXEC)

clean:
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -rf $(EXEC)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
