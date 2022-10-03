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

static t_statement	*load_statement(t_parser *parser, const char *name)
{
	t_op		*op;
	t_statement	statement;
	size_t		index;

	op = opmap_get(opmap, name);
	if (!op)
		return (NULL);
	statement.op = *op;
	statement.acb = 0;
	statement.arguments = {0};
	index = parser->body.len;
	if (vec_push(&parser->body, &statement) == ERROR)
		return (NULL);
	return ((t_statement *) vec_get(&parser->body, index));
}

static int	parse_arguments(t_statement *statement, t_lexer *lexer)
{
	uint8_t	index;

	index = 0;

	while (index < statement->op.argc)
	{
	}
}

int	parse_operation(t_parser *parser, t_lexer *lexer)
{
	t_symbols	*sym;
	char		*name;
	t_statement	*statement;

	sym = &parser->sym;
	name = symbol_str(sym);
	ft_printf("%s\n", name);
	statement = load_statement(parser, name);
	if (!statement)
		return (ERROR);
	parse_arguments();
}
