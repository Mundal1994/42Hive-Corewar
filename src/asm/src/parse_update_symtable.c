/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_update_symtable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:47:18 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 19:46:13 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtable.h"
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

static int	enter_new(t_symtable *symtable, const char *name,
		t_symentry newentry)
{
	t_vec	*entries;
	int		value;

	entries = &symtable->entries;
	value = entries->len;
	if (!hashmap_try_insert(&symtable->map, name, value)
		|| vec_push(entries, &newentry) == ERROR)
		return (ERROR);
	return (OK);
}

static void	update_argument(t_parser *parser, size_t index, uint8_t arg_n, size_t location)
{
	t_statement	*statement;
	t_arg		*arg;

	statement = (t_statement *) vec_get(&parser->body, index);
	arg = &statement->arguments[arg_n];
	arg->dir = location - arg->dir;
}

static int	complete_references(t_symentry *entry, t_parser *parser, t_symentry newentry)
{
	t_forwardrefs	*link;

	entry->defined = newentry.defined;
	entry->location = newentry.location;
	update_argument(parser, entry->statement_id, entry->arg, newentry.location);
	link = entry->flink;
	while (link)
	{
		update_argument(parser, link->statement_id, link->arg, newentry.location);
		link = link->nlink;
	}
	return (OK);
}


int	parse_update_symtable(t_parser *parser, const char *name,
		t_symentry newentry)
{
	t_symtable	*symtable;
	t_symentry	*entry;

	symtable = &parser->symtable;
	entry = symtable_find(symtable, name);
	if (!entry)
		return (enter_new(symtable, name, newentry));
	if (entry->defined)
	{
		if (!newentry.defined)
		{
			update_argument(parser, newentry.statement_id, newentry.arg, entry->location);
			return (OK);
		}
		return (warning_ret(SYMTABLE_DUP));
	}
	if (!newentry.defined)
		return (new_reference(&entry->flink, newentry));
	return (complete_references(entry, parser, newentry));
}
