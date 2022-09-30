/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:55:21 by cchen             #+#    #+#             */
/*   Updated: 2022/09/30 10:55:22 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	parser_str(t_lexer *lexer, t_symbol *sym, char *dst, size_t size)
{
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (sym->type != LA_cmdstr)
		return (ERROR);
	if (sym->str.length > size)
		return (ERROR);
	ft_memcpy(dst, symbol_str(sym), sym->str.length);
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (sym->type != LA_eol)
		return (ERROR);
	return (OK);

}

static int	parse_name(t_lexer *lexer, t_symbol *sym, char *dst)
{
	static bool	exists;

	if (exists)
		return (error(errorset(lexer->source.pos, sym->str), NAME_EXISTS));
	exists = 1;
	return (parse_str(lexer, sym, dst, PROG_NAME_LENGTH));
}

static int	parse_comment(t_lexer *lexer, t_symbol *sym, char *dst)
{
	static bool	exists;

	if (exists)
		return (error(errorset(lexer->source.pos, sym->str), NAME_EXISTS));
	exists = 1;
	return (parse_str(lexer, sym, dst, COMMENT_LENGTH));
}

static int	parse_headerline(t_parser *parser, t_lexer *lexer)
{
	static int	tracker;
	t_symbols	*sym;

	sym = &parser->sym;
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	while (sym->type == LA_eol)
	{
		if (lexer_next(lexer, sym) == ERROR)
			return (ERROR);
	}
	if (sym->type != LA_cmd)
		return (error(errorset(lexer->source.pos, sym->str), PARSER_EXPECT_CMD));
	if (ft_strequ(symbol_str(sym), NAME_CMD_STRING))
		return (parse_name(lexer, sym, parser->header.prog_name));
	if (ft_strequ(symbol_str(sym), COMMENT_CMD_STRING))
		return (parse_line(lexer, sym, parser->header.comment, COMMENT_LENGTH));
	return (error(errorset(lexer->source.pos, sym->str), PARSER_UNKNOWN_CMD_STR));
}

int	parse_header(t_parser *parser, t_lexer *lexer)
{
	t_symbols	*sym;

	sym = &parser->sym;
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	while (sym->type == LA_eol)
	{
		if (lexer_next(lexer, sym) == ERROR)
			return (ERROR);
	}
	while (parse_headerline(parser, lexer) == OK)
	{
	}
}
