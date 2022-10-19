/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_indirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:18:46 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 22:41:57 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* Parses indirect argument types, and calls parse_reference or parse_numeric
 * on the symbol depending on the argtype */
int	parse_indirect(t_parser *parser, t_lexer *lexer, t_statement *statement,
		uint8_t index)
{
	t_symbols	*sym;

	sym = &parser->sym;
	statement->acb |= IND_CODE << (3 - index) * 2;
	parser->size += 2;
	if (sym->argtype & T_LAB)
		return (parse_reference(parser, lexer, statement, index));
	return (parse_numeric(statement, lexer, sym, index));
}
