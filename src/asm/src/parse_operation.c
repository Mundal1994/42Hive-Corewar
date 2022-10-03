/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:10:02 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 11:10:03 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	load_statement(t_parser *parser, const char *name)
{
	t_op		*op;
	t_statement	statement;
	size_t		index;

	op = opmap_get(&parser->opmap, name);
	if (!op)
		return (ERROR);
	statement.op = *op;
	statement.acb = 0;
	ft_bzero(statement.arguments, sizeof(t_arg) * 3);
	index = parser->body.len;
	if (vec_push(&parser->body, &statement) == ERROR)
		return (ERROR);
	return (OK);
}

static int	next_argument(t_parser *parser, t_lexer *lexer, uint8_t index)
{
	t_statement	*statement;
	t_symbols	*sym;

	statement = (t_statement *)vec_get(&parser->body, parser->body.len - 1);
	sym = &parser->sym;
	if (sym->type == LA_eol || sym->type == LA_com)
		return (error(errorset(lexer->source.pos, sym->str),
			PARSER_INSUF_ARG));
	if (!(statement->op.arg_types[index] & sym->argtype))
		return (error(errorset(lexer->source.pos, sym->str),
			PARSER_WRONG_ARG));
	if (sym->argtype & T_REG)
		return (parse_register(statement, lexer, sym, index));
	if (sym->argtype & T_DIR)
		return (parse_direct(statement, lexer, sym, index));
	if (sym->argtype & T_IND)
		return (parse_indirect(statement, lexer, sym, index));
	return (error(errorset(lexer->source.pos, sym->str), PARSER_UNKNOWN_ARG));
}

static int	parse_arguments(t_parser *parser, t_lexer *lexer)
{
	uint8_t		index;
	t_statement	*statement;
	t_symbols	*sym;

	sym = &parser->sym;
	statement = (t_statement *)vec_get(&parser->body, parser->body.len - 1);
	index = 0;
	while (index < statement->op.argc)
	{
		if (lexer_next(lexer, sym) == ERROR)
			return (ERROR);
		if (next_argument(parser, lexer, index) == ERROR)
			return (ERROR);
		++index;
	}
	return (OK);
}

int	parse_operation(t_parser *parser, t_lexer *lexer)
{
	t_symbols	*sym;
	char		*name;

	sym = &parser->sym;
	name = symbol_str(sym);
	ft_printf("%s\n", name);
	if (load_statement(parser, name) == ERROR)
		return (ERROR);
	return (parse_arguments(parser, lexer));
}
