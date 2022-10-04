/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:58:53 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 08:55:47 by caruychen        ###   ########.fr       */
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
	parser->size = 0;
	if (symbol_init(&parser->sym) != ERROR
		&& vec_new(&parser->body, 1, sizeof(t_statement)) != ERROR
		&& opmap_new(&parser->opmap) != ERROR
		&& symtable_init(&parser->symtable) != ERROR)
		return ;
	parse_free(parser);
	lexer_free(lexer);
	exit_error();
}

void	parse_free(t_parser *parser)
{
	if (parser->sym.str.memory)
		symbol_free(&parser->sym);
	if (parser->body.memory)
		vec_free(&parser->body);
	if (parser->opmap.entries)
		opmap_free(&parser->opmap);
	symtable_free(&parser->symtable);
}

t_symentry	parse_newsym(t_parser *parser, uint8_t arg)
{
	t_symbols	sym;
	t_symentry	newentry;

	sym = parser->sym;
	newentry.defined = sym.type == LA_label;
	newentry.statement_id = parser->body.len - 1 * (sym.type == LA_ref);
	newentry.arg = arg;
	newentry.location = parser->size;
	newentry.flink = NULL;
	return (newentry);
}

int	parse(t_parser *parser, t_lexer *lexer)
{
	if (parse_header(parser, lexer) == ERROR)
		return (ERROR);
	parse_body(parser, lexer);
	return (OK);
}
