/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:19:06 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 18:56:12 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include "lexer.h"
# include "errors.h"
# include "opmap.h"

typedef enum s_start
{
	ST_label = 1,
	ST_op,
	ST_all
}			t_start;

typedef union s_arg
{
	uint8_t		reg;
	uint16_t	ind;
	uint32_t	dir;	
}		t_arg;

typedef struct s_statement
{
	t_op	op;
	uint8_t	acb;
	t_arg	arguments[3];
}		t_statement;

typedef struct s_syntax
{
	t_start			instr: 2;
}		t_syntax;

typedef struct s_parser
{
	t_symbols	sym;
	t_syntax	syntax;
	t_header	header;
	t_vec		body;
	t_hashmap	opmap;
}		t_parser;

void	parse_init(t_parser *parser, t_lexer *lexer);
void	parse_free(t_parser *parser);
int		parse(t_parser *parser, t_lexer *lexer);
int		parse_header(t_parser *parser, t_lexer *lexer);

#endif
