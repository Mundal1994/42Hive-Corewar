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

static t_arg	*populate_arg(t_statement *statement, t_symbols *sym, uint8_t index)
{
	t_arg	*arg;

	arg = &statement->arguments[index];
	if (sym->argtype & T_DIR)
		arg->dir = statement->pos;
	if (sym->argtype & T_IND)
		arg->ind = (uint16_t) statement->pos;
	return (arg);
}

static int	update_symtable(t_symtable *symtable, t_symbols *sym, t_arg *arg)
{
	t_symentry	newentry;

	newentry = symtable_newentry(false, arg, 0);
	if (symtable_enter(symtable, symbol_str(sym), newentry) == ERROR)
		return (ERROR);
	return (OK);
}

int	parse_reference(t_parser *parser, t_lexer *lexer, t_statement *statement,
		uint8_t index)
{
	t_symbols	*sym;
	t_arg		*arg;

	sym = &parser->sym;
	arg = populate_arg(statement, sym, index);
	if (update_symtable(&parser->symtable, sym, arg) == ERROR)
		return (ERROR);
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_arg_end(lexer, sym, statement, index));
}
