/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcodes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:10:51 by cchen             #+#    #+#             */
/*   Updated: 2022/09/18 09:38:25 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPCODES_H
# define OPCODES_H

# include "op.h"
# include <stdint.h>
# include <stdbool.h>

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

typedef enum e_opindex
{
	IDX_LIVE,
	IDX_LD,
	IDX_ST,
	IDX_ADD,
	IDX_SUB,
	IDX_AND,
	IDX_OR,
	IDX_XOR,
	IDX_ZJMP,
	IDX_LDI,
	IDX_STI,
	IDX_FORK,
	IDX_LLD,
	IDX_LLDI,
	IDX_LFORK,
	IDX_AFF,
	IDX_NULL
}			t_opindex;

typedef struct s_op {
	char		*name;
	uint8_t		argument_num;
	t_arg_type	arguments[3];
	uint8_t		opcode;
	uint16_t	cycle_cost;
	char		*description;
	bool		no_acb;
	bool		label;
}				t_op;

#endif
