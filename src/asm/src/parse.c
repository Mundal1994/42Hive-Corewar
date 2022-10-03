/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:58:53 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 08:52:22 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	parse_init(t_parser *parser, t_lexer *lexer)
{
	t_header	*header;

	header = &parser->header;
	header->magic = COREWAR_EXEC_MAGIC;
	header->prog_size = 0;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	if (symbol_init(&parser->sym) == OK)
		return ;
	lexer_free(lexer);
	exit_error();
}

int	parse_line(t_lexer *lexer, t_symbols *sym)
{
	while (lexer_next(lexer, sym) == OK && sym->type > LA_eol)
	{
		
	}
}

int	parse(t_lexer *lexer)
{
	t_parser	parser;

	parse_init(lexer, &sym);
	parse_header(lexer, &sym);
	parse_body(lexer &sym);
	symbol_free(&sym);
	return (OK);
}
