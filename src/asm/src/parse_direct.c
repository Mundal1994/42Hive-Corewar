/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_direct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:18:35 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 22:48:16 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_direct(t_parser *parser, t_lexer *lexer, t_statement *statement,
	uint8_t index)
{
	t_symbols	*sym;

	sym = &parser->sym;
	statement->arguments[index].dir = (uint32_t) sym->num;
	parser->size += 2 + 2 * !statement->op.label;
	if (sym->argtype & T_LAB)
		return (parse_reference(statement, lexer, sym, index));
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_numeric(statement, lexer, sym, index));
}
