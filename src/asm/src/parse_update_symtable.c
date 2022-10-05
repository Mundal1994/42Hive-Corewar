/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_update_symtable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:47:18 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 22:52:53 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	new_reference(t_forwardrefs **newref, t_symentry newentry)
{
	if (!(*newref))
	{
		*newref = (t_forwardrefs *) ft_memalloc(sizeof(t_forwardrefs));
		if (!*newref)
			return (ERROR);
		(*newref)->statement_id = newentry.statement_id;
		(*newref)->arg = newentry.arg;
		return (OK);
	}
	return (new_reference(&(*newref)->nlink, newentry));
}

static t_symentry	new_entry(t_parser *parser, uint8_t arg)
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

static void	update_argument(t_parser *parser, size_t index,
		uint8_t arg_n, size_t location)
{
	t_statement	*statement;
	t_arg		*arg;

	statement = (t_statement *) vec_get(&parser->body, index);
	arg = &statement->arguments[arg_n];
	arg->dir = location - arg->dir;
}

static void	complete_references(t_symentry *entry, t_parser *parser,
		t_symentry newentry)
{
	t_forwardrefs	*link;

	entry->defined = newentry.defined;
	entry->location = newentry.location;
	update_argument(parser, entry->statement_id, entry->arg, newentry.location);
	link = entry->flink;
	while (link)
	{
		update_argument(parser, link->statement_id, link->arg,
			newentry.location);
		link = link->nlink;
	}
}

int	parse_update_symtable(t_parser *parser, const char *name,
		uint8_t arg)
{
	t_symtable	*symtable;
	t_symentry	*entry;
	t_symentry	newentry;

	symtable = &parser->symtable;
	newentry = new_entry(parser, arg);
	entry = symtable_find(symtable, name);
	if (!entry)
		return (symtable_add(symtable, name, newentry));
	if (entry->defined)
	{
		if (!newentry.defined)
			return (update_argument(parser, newentry.statement_id,
					newentry.arg, entry->location), OK);
		return (warning_ret(SYMTABLE_DUP));
	}
	if (!newentry.defined)
		return (new_reference(&entry->flink, newentry));
	return (complete_references(entry, parser, newentry), OK);
}
