/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reference.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:58:37 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/07 11:44:25 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include "parse.h"

static void	populate_arg(t_statement *statement, t_symbols *sym, uint8_t index)
{
	t_arg	*arg;

	arg = &statement->arguments[index];
	if (sym->argtype & T_DIR)
		arg->dir = statement->pos;
	if (sym->argtype & T_IND)
		arg->ind = (uint16_t) statement->pos;
}

static int	is_mathsym(t_symbols *sym)
{
	return (sym->type == LA_plus || sym->type == LA_minus);
}

static void	recalculate_arg(t_statement *statement, t_arg orig, uint8_t index)
{
	t_arg	*arg;
	long	diff;

	arg = &statement->arguments[index];
	diff = arg->dir - orig.dir;
	arg->dir = orig.dir - diff;
}

/* Parses labels in arguments, updates the forward reference symbol table */
int	parse_reference(t_parser *parser, t_lexer *lexer, t_statement *statement,
		uint8_t index)
{
	t_symbols	*sym;
	t_arg		orig;
	bool		is_sym_defined;

	sym = &parser->sym;
	populate_arg(statement, sym, index);
	orig = statement->arguments[index];
	is_sym_defined = symtable_is_defined(&parser->symtable, symbol_str(sym));
	if (parse_update_symtable(parser, symbol_str(sym), index) == ERROR
		|| lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (is_mathsym(sym) && parse_math(statement, lexer, sym, index) == ERROR)
		return (ERROR);
	if (!is_sym_defined)
		recalculate_arg(statement, orig, index);
	return (parse_arg_end(lexer, sym, statement, index));
}
