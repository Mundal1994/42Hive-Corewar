/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_register.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:56:33 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 22:40:35 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include "parse.h"

/* Parses register argument type */
int	parse_register(t_parser *parser, t_lexer *lexer, t_statement *statement,
		uint8_t index)
{
	t_symbols	*sym;

	sym = &parser->sym;
	statement->acb |= REG_CODE << (3 - index) * 2;
	statement->arguments[index].reg = (uint8_t) sym->num;
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (++parser->size, parse_arg_end(lexer, sym, statement, index));
}
