/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:58:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 18:37:05 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_init(t_parser *parser, t_lexer *lexer)
{
	t_header	*header;

	header = &parser->header;
	header->magic = COREWAR_EXEC_MAGIC;
	header->prog_size = 0;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	if (symbol_init(&parser->sym) != ERROR
		&& vec_new(&parser->body, 1, sizeof(t_statement)) != ERROR
		&& opmap_new(&parser->opmap) != ERROR)
		return ;
	parse_free(parser)
	lexer_free(lexer);
	exit_error();
}

void parse_free(t_parser *parser)
{
	if (parser->sym.str.memory)
		symbol_free(&parser->sym);
	if (parser->body.memory)
		vec_free(&parser->body);
	if (parser->opmap.entries)
		opmap_free(&parser->opmap);
}

int	parse(t_parser *parser, t_lexer *lexer)
{
	parse_header(parser, lexer);
	parse_body(parser, lexer);
	return (OK);
}
