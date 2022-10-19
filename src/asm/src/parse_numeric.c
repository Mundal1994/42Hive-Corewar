/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:26:55 by cchen             #+#    #+#             */
/*   Updated: 2022/10/07 10:50:19 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "definitions.h"
#include "parse.h"

static int	filter_types(t_lexer *lexer, t_symbols *sym, t_arg *arg)
{
	t_errorset	error_set;

	error_set = errorset(lexer->source.pos, sym->str);
	if (sym->type != LA_num)
		return (error(error_set, PARSER_EXPECT_NUM));
	if (sym->argtype & (T_REG | T_LAB))
		return (error(error_set, PARSER_WRONG_ARG));
	if (sym->argtype & T_DIR)
		return (arg->dir = (uint32_t) sym->num, OK);
	if (sym->argtype & T_IND)
		return (arg->ind = (uint16_t) sym->num, OK);
	return (error(error_set, PARSER_UNKNOWN_ARGTYPE));
}

static int	is_mathsym(t_symbols *sym)
{
	return (sym->type == LA_plus || sym->type == LA_minus);
}

/* Parses numeric argument data, and calls parse_math on any mathematical
 * operations */
int	parse_numeric(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	t_arg	*arg;

	arg = statement->arguments + index;
	if (filter_types(lexer, sym, arg) == ERROR
		|| lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (is_mathsym(sym) && parse_math(statement, lexer, sym, index) == ERROR)
		return (ERROR);
	return (parse_arg_end(lexer, sym, statement, index));
}
