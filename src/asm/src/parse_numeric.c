/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:26:55 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 22:56:39 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool	is_endof_arg(t_symtypes type, uint8_t argc, uint8_t index)
{
	if (index < argc - 1)
		return (type == LA_comma);
	return (type == LA_eol || type == LA_com);
}

static int	get_action(t_lexer *lexer, int *action, t_symbols *sym)
{
	if (sym->type != LA_plus && sym->type != LA_minus)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_EXPECT_MATH_OP));
	*action = 1 * (sym->type == LA_plus) - 1 * (sym->type == LA_minus);
	return (OK);
}

static int	get_number(t_arg *arg, t_lexer *lexer, t_symbols *sym, int *action)
{
	t_errorset	error_set;

	error_set = errorset(lexer->source.pos, sym->str);
	if (sym->type != LA_num || sym->argtype & (T_DIR | T_REG | T_LAB))
		return (error(error_set, PARSER_EXPECT_NUM));
	if (sym->argtype & T_DIR)
		arg->dir += (uint32_t)(*action * sym->num);
	if (sym->argtype & T_IND)
		arg->ind += (uint16_t)(*action * sym->num);
	*action = 0;
	return (OK);
}

int	parse_numeric(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	int		action;
	t_arg	*arg;

	arg = statement->arguments + index;
	action = 0;
	while (!is_endof_arg(sym->type, statement->op.argc, index))
	{
		if (action == 0)
		{
			if (get_action(lexer, &action, sym) == ERROR)
				return (ERROR);
		}
		else
		{
			if (get_number(arg, lexer, sym, &action) == ERROR)
				return (ERROR);
		}
		if (lexer_next(lexer, sym) == ERROR)
			return (ERROR);
	}
	if (action != 0)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_EXPECT_NUM));
	return (parse_arg_end(lexer, sym, statement, index));
}
