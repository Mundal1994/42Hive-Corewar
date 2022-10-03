/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:16:40 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 10:16:44 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	parse_label(t_parser *parser, t_lexer *lexer)
{
	t_symbols	*sym;

	sym = &parser->sym;
	ft_printf("%s\n", symbol_str(sym));
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (sym->type == LA_eol)
		return (OK);
	if (sym->type == LA_instr)
		return (parse_operation(parser, lexer));
	return (error(errorset(lexer->source.pos, sym->str),
		PARSER_EXPECT_INSTR));
}

static int	parse_line(t_parser *parser, t_lexer *lexer)
{
	t_symbols	*sym;

	sym = &parser->sym;
	if (lexer_nextline(lexer, sym) == ERROR)
		return (ERROR);
	if (sym->type == LA_label)
		return (parse_label(parser, lexer));
	if (sym->type == LA_instr)
		return (parse_operation(parser, lexer));
	return (error(errorset(lexer->source.pos, sym->str),
		PARSER_EXPECT_START));
}

int	parse_body(t_parser *parser, t_lexer *lexer)
{
}
