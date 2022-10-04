/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_update_symtable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:47:18 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 16:47:19 by cchen            ###   ########.fr       */
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

static int	complete_references(t_symentry *entry, t_parser *parser, t_symentry newentry)
{
	t_forwardrefs	*link;
	t_statement		*statement;
	t_arg			*arg;

	entry->defined = newentry.defined;
	entry->location = newentry.location;
	statement = (t_statement *) vec_get(&parser->body, entry->statement_id);
	arg = &statement->arguments[entry->arg];
	arg->dir = newentry.location - arg->dir;
	link = entry->flink;
	while (link)
	{
		statement = (t_statement *) vec_get(&parser->body, link->statement_id);
		arg = &statement->arguments[link->arg];
		arg->dir = newentry.location - arg->dir;
		link = link->nlink;
	}
	return (OK);
}

int	parse_update_symtable(t_parser *parser, const char *name,
		t_symentry newentry)
{
	t_symtable	*symtable;
	t_symentry	*entry;
	t_statement	*statement;
	t_arg		*arg;

	symtable = &parser->symtable;
	entry = symtable_find(symtable, name);
	if (!entry)
		return (enter_new(symtable, name, newentry));
	if (entry->defined)
	{
		if (!newentry.defined)
		{
			statement = (t_statement *) vec_get(&parser->body, newentry.statement_id);
			arg = &statement->arguments[newentry.arg];
			arg->dir = entry->location - arg->dir;
			return (OK);
		}
		return (warning_ret(SYMTABLE_DUP));
	}
	if (!newentry.defined)
		return (new_reference(&entry->flink, newentry));
	return (complete_references(entry, parser, newentry));
}
