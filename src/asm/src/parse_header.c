/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:07:09 by cchen             #+#    #+#             */
/*   Updated: 2022/09/30 18:29:36 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	parse_str(t_lexer *lexer, t_symbols *sym, char *dst, size_t size)
{
	t_errorset	error_set;

	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	error_set = errorset(lexer->source.pos, sym->str);
	if (sym->type != LA_cmdstr)
		return (error(error_set, PARSER_NO_QUOTE));
	if (sym->str.length > size)
		return (error_no_str(error_set, PARSER_STR_TOO_LONG));
	ft_memcpy(dst, symbol_str(sym), sym->str.length);
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (sym->type == LA_com && lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	error_set = errorset(lexer->source.pos, sym->str);
	if (sym->type != LA_eol)
		return (error(error_set, PARSER_NO_EOL));
	return (OK);
}

static int	parse_name(t_lexer *lexer, t_symbols *sym, char *dst)
{
	static bool	exists;

	if (exists)
		return (error(errorset(lexer->source.pos, sym->str), NAME_EXISTS));
	exists = 1;
	return (parse_str(lexer, sym, dst, PROG_NAME_LENGTH));
}

static int	parse_comment(t_lexer *lexer, t_symbols *sym, char *dst)
{
	static bool	exists;

	if (exists)
		return (error(errorset(lexer->source.pos, sym->str), NAME_EXISTS));
	exists = 1;
	return (parse_str(lexer, sym, dst, COMMENT_LENGTH));
}

static int	parse_headerline(t_parser *parser, t_lexer *lexer)
{
	t_symbols	*sym;

	sym = &parser->sym;
	if (lexer_nextline(lexer, sym) == ERROR)
		return (ERROR);
	if (sym->type != LA_cmd)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_EXPECT_CMD));
	if (ft_strequ(symbol_str(sym), NAME_CMD_STRING))
		return (parse_name(lexer, sym, parser->header.prog_name));
	if (ft_strequ(symbol_str(sym), COMMENT_CMD_STRING))
		return (parse_comment(lexer, sym, parser->header.comment));
	return (error(errorset(lexer->source.pos, sym->str),
			PARSER_UNKNOWN_CMD));
}

int	parse_header(t_parser *parser, t_lexer *lexer)
{
	if (parse_headerline(parser, lexer) == OK
		&& parse_headerline(parser, lexer) == OK)
		return (OK);
	return (ERROR);
}
