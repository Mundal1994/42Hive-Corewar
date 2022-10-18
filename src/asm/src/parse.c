/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:58:53 by cchen             #+#    #+#             */
/*   Updated: 2022/10/17 10:52:04 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** *
 * There are three phases to Parsing:
 * 1. Source handling
 *   - Source character handler. Scans the source text, returning a character
 *     at a time, and analyses the source into lines.
 *   - Keeps track of its position in the source text, as well as row & column.
 * 2. Lexical analysis
 *   - Scans source characters, and converts the sequence of characters into
 *     a sequence of lexical tokens.
 *   - A valid token is emitted as a "symbol", defined in symbol.h
 *   - A symbol (token) can be one of 14 different types, defined in symbol.h
 * 3. Syntax analysis
 *   - Analyses the string of symbols produced by the lexer.
 *   - Syntax tree rules are encoded into parse_body.c.
 *   - The symbols emitted by the lexer are analysed for correctness against
 *     he grammatical rules of the Corewar assembly language.
 *   - Labels are handled using a "symbol table handler", defined in symtable.h
 *     and symtable.c. Symtable is necessary to deadl with forward references
 *     to labels in the operations arguments.
 * ************************************************************************* */

#include <stdlib.h>
#include "errors.h"
#include "definitions.h"
#include "parse.h"

static void	parse_init(t_parser *parser, t_lexer *lexer)
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

/* Single pass parser, performing lexical and syntax analysis */
void	parse(t_parser *parser, const char *arg)
{
	t_lexer	lexer;

	lexer_init(&lexer, arg);
	parse_init(parser, &lexer);
	if (parse_header(parser, &lexer) == ERROR
		|| parse_body(parser, &lexer) == ERROR)
	{
		parse_free(parser);
		lexer_free(&lexer);
		exit(EXIT_FAILURE);
	}
	lexer_free(&lexer);
}

/* Free's memory allocated to the parser */
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
