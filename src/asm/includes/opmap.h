/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opmap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:05:33 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 22:35:23 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPMAP_H
# define OPMAP_H

# include <stdbool.h>
# include <stdint.h>
# include "op.h"
# include "hashmap.h"

# define MAX_ARGS 3

typedef enum e_opcodes
{
	OP_NULL,
	OP_LIVE,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF
}			t_opcodes;

typedef struct s_op
{
	char		*name;
	uint8_t		argc;
	t_arg_type	arg_types[MAX_ARGS];
	uint8_t		opcode;
	bool		acb;
	bool		label;
}				t_op;

int		opmap_new(t_hashmap *opmap);
t_op	*opmap_get(t_hashmap *opmap, const char *key);
void	opmap_free(t_hashmap *opmap);

#endif
