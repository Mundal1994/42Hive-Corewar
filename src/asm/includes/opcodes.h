/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcodes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:39:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 09:39:48 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPCODES_H
# define OPCODES_H

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
	t_arg_type	arg_types[3];
	uint8_t		opcode;
	bool		no_acb;
	bool		label;
}				t_op;

#endif
