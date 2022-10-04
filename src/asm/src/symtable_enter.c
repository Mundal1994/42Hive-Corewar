/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable_enter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:19:12 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/04 11:02:00 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtable.h"

static int	enter_new(t_symtable *symtable, const char *name,
		t_symentry entry)
{
	t_vec	*entries;
	int		value;

	entries = &symtable->entries;
	value = entries->len;
	if (!hashmap_try_insert(&symtable->map, name, value)
		|| vec_push(entries, &entry) == ERROR)
		return (ERROR);
	return (OK);
}

static int	new_reference(t_forwardrefs **newref, t_symentry newentry)
{
	*newref = (t_forwardrefs *) ft_memalloc(sizeof(**newref));
	if (!*newref)
		return (ERROR);
	(*newref)->arg = newentry.arg;
	(*newref)->nlink = NULL;
	return (OK);
}

static int	add_reference(t_symentry *entry, t_symentry newentry)
{
	t_forwardrefs	*link;

	if (!entry->flink)
		return (new_reference(&entry->flink, newentry));
	link = entry->flink;
	while (link->nlink)
		link = link->nlink;
	return (new_reference(&link->nlink, newentry));
}

static int	complete_entry(t_symentry *entry, t_symentry newentry)
{
	t_forwardrefs	*link;

	entry->defined = newentry.defined;
	entry->location = newentry.location;
	link = entry->flink;
	while (link)
	{
		link->arg->dir = newentry.location - link->arg->dir;
		link = link->nlink;
	}
	return (OK);
}

int	symtable_enter(t_symtable *symtable, const char *name,
		t_symentry newentry)
{
	t_symentry	*entry;

	entry = symtable_find(symtable, name);
	if (!entry)
		return (enter_new(symtable, name, newentry));
	if (entry->defined)
	{
		if (newentry.arg)
			return (newentry.arg->dir = entry->location - newentry.arg->dir, OK);
		return (warning_ret(SYMTABLE_DUP));
	}
	if (!newentry.defined)
		return (add_reference(entry, newentry));
	return (complete_entry(entry, newentry));
}
