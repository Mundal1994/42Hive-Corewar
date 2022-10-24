/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:10:02 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 22:56:14 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "definitions.h"
#include "parse.h"

/* Loads the correct operation based on the instruction symbol and optable,
 * returns ERROR if the operation doesn't exist */
static int	load_statement(t_parser *parser, t_lexer *lexer)
{
	const t_op		*op;
	t_statement		statement;
	t_symbols		*sym;

	sym = &parser->sym;
	op = opmap_get(&parser->opmap, symbol_str(sym));
	if (!op)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_UNKNOWN_INSTR));
	statement.op = *op;
	statement.acb = 0;
	ft_bzero(statement.arguments, sizeof(t_arg) * 3);
	statement.pos = parser->size;
	if (vec_push(&parser->body, &statement) == ERROR)
		return (ERROR);
	return (OK);
}

/* Parses the next argument in the operation, determining whether it is
 * a register, direct, or indirect argument */
static int	next_argument(t_parser *parser, t_lexer *lexer,
		t_statement *statement, uint8_t index)
{
	t_symbols	*sym;

	sym = &parser->sym;
	if (sym->type == LA_eol || sym->type == LA_com)
		return (error_no_str(errorset(lexer->source.pos, sym->str),
				PARSER_INSUF_ARG));
	if (!(statement->op.arg_types[index] & sym->argtype))
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_WRONG_ARG));
	if (sym->argtype & T_REG)
		return (parse_register(parser, lexer, statement, index));
	if (sym->argtype & T_DIR)
		return (parse_direct(parser, lexer, statement, index));
	if (sym->argtype & T_IND)
		return (parse_indirect(parser, lexer, statement, index));
	return (error(errorset(lexer->source.pos, sym->str), PARSER_UNKNOWN_ARG));
}

/* Reads all relevant arguments from the source, depending on the operation */
static int	parse_arguments(t_parser *parser, t_lexer *lexer)
{
	uint8_t		index;
	t_statement	*statement;
	t_symbols	*sym;

	sym = &parser->sym;
	statement = (t_statement *)vec_get(&parser->body, parser->body.len - 1);
	parser->size += statement->op.acb;
	index = 0;
	while (index < statement->op.argc)
	{
		if (lexer_next(lexer, sym) == ERROR)
			return (ERROR);
		if (next_argument(parser, lexer, statement, index) == ERROR)
			return (ERROR);
		++index;
	}
	return (OK);
}

/* Checks that the instruction exists in the op table, and parses arguments */
int	parse_operation(t_parser *parser, t_lexer *lexer)
{
	if (load_statement(parser, lexer) == ERROR)
		return (ERROR);
	return (++parser->size, parse_arguments(parser, lexer));
}
