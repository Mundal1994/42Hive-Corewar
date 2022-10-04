/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_indirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:18:46 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 11:04:13 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_indirect(t_parser *parser, t_lexer *lexer, t_statement *statement,
		uint8_t index)
{
	t_symbols	*sym;

	sym = &parser->sym;
	statement->arguments[index].ind = (uint16_t) sym->num;
	parser->size += 2;
	if (sym->argtype & T_LAB)
		return (parse_reference(parser, lexer, statement, index));
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_numeric(statement, lexer, sym, index));
}
