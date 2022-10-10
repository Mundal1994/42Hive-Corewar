/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:19:06 by cchen             #+#    #+#             */
/*   Updated: 2022/10/07 09:41:20 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"
# include "opmap.h"
# include "symtable.h"

typedef union s_arg
{
	uint8_t		reg;
	uint16_t	ind;
	uint32_t	dir;	
}		t_arg;

typedef struct s_statement
{
	t_op		op;
	uint8_t		acb;
	t_arg		arguments[3];
	uint32_t	pos;
}		t_statement;

typedef struct s_parser
{
	t_symbols	sym;
	t_hashmap	opmap;
	t_symtable	symtable;
	t_header	header;
	t_vec		body;
	uint32_t	size;
}		t_parser;

void	parse_free(t_parser *parser);
void	parse(t_parser *parser, const char *arg);
int		parse_header(t_parser *parser, t_lexer *lexer);
int		parse_body(t_parser *parser, t_lexer *lexer);
int		parse_operation(t_parser *parser, t_lexer *lexer);
int		parse_register(t_parser *parser, t_lexer *lexer,
			t_statement *statement, uint8_t index);
int		parse_direct(t_parser *parser, t_lexer *lexer,
			t_statement *statement, uint8_t index);
int		parse_indirect(t_parser *parser, t_lexer *lexer,
			t_statement *statement, uint8_t index);
int		parse_reference(t_parser *parser, t_lexer *lexer,
			t_statement *statement, uint8_t index);
int		parse_numeric(t_statement *statement, t_lexer *lexer,
			t_symbols *sym, uint8_t index);
int		parse_math(t_statement *statement, t_lexer *lexer,
			t_symbols *sym, uint8_t index);
int		parse_arg_end(t_lexer *lexer, t_symbols *sym,
			t_statement *statement, uint8_t index);
int		parse_update_symtable(t_parser *parser,
			const char *name, uint8_t arg);

#endif
