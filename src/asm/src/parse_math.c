/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:09:37 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/07 10:47:31 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool	is_endof_arg(t_symtypes type)
{
	return (type == LA_comma || type == LA_eol || type == LA_com);
}

static int	get_action(t_lexer *lexer, int *action, t_symbols *sym)
{
	if (sym->type != LA_plus && sym->type != LA_minus)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_EXPECT_MATH_OP));
	*action = 1 * (sym->type == LA_plus) - 1 * (sym->type == LA_minus);
	return (lexer_next(lexer, sym));
}

static int	get_number(t_arg *arg, t_lexer *lexer, t_symbols *sym, int *action)
{
	t_errorset	error_set;

	error_set = errorset(lexer->source.pos, sym->str);
	if (sym->type != LA_num)
		return (error(error_set, PARSER_EXPECT_NUM));
	if (sym->argtype & (T_REG | T_LAB))
		return (error(error_set, PARSER_WRONG_ARG));
	arg->dir += (uint32_t)(*action * sym->num);
	*action = 0;
	return (lexer_next(lexer, sym));
}

static int	get_next_op(t_arg *arg, t_lexer *lexer, t_symbols *sym, int *action)
{
	if (*action == 0)
		return (get_action(lexer, action, sym));
	return (get_number(arg, lexer, sym, action));
}

int	parse_math(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	int		action;
	t_arg	*arg;

	arg = statement->arguments + index;
	action = 0;
	while (!is_endof_arg(sym->type))
	{
		if (get_next_op(arg, lexer, sym, &action) == ERROR)
			return (ERROR);
	}
	if (action != 0)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_EXPECT_NUM));
	return (OK);
}
