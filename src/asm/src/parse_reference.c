/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reference.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:58:37 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/04 10:56:16 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	populate_arg(t_statement *statement, t_symbols *sym, uint8_t index)
{
	t_arg	*arg;

	arg = &statement->arguments[index];
	if (sym->argtype & T_DIR)
		arg->dir = statement->pos;
	if (sym->argtype & T_IND)
		arg->ind = (uint16_t) statement->pos;
}

int	parse_reference(t_parser *parser, t_lexer *lexer, t_statement *statement,
		uint8_t index)
{
	t_symbols	*sym;
	t_symentry	newentry;

	sym = &parser->sym;
	populate_arg(statement, sym, index);
	newentry = parse_newsym(parser, index);
	if (parse_update_symtable(parser, symbol_str(sym), newentry) == ERROR)
		return (ERROR);
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_arg_end(lexer, sym, statement, index));
}
