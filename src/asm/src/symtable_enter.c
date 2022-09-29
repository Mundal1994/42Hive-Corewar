/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable_enter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:19:12 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/29 15:54:06 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_symentry *enter_new(t_symtable *symtable, const char *name,
		t_symentry entry)
{
	t_vec	*entries;
	int	value;

	entries = &symtable->entries;
	value = entries->len;
	if (!hashmap_try_insert(&symtable->map, name, value)
		|| vec_push(entries, &entry) == ERROR)
		return (NULL);
	return ((t_symentry *)vec_get(entries, value));
}

static t_forwardrefs	*new_reference(t_symentry newentry)
{
	t_forwardrefs	*newref;

	newref = (t_forwardrefs *) ft_memalloc(sizeof(*newref));
	newref->location = newentry.location;
	newref->nlink = NULL;
	return (newref);
}

static t_symentry	*add_reference(t_symentry *entry, t_symentry newentry)
{
	t_forwardrefs	*link;

	if (!entry->flink)
		return (entry->flink = new_reference(newentry), entry);
	link = entry->flink;
	while (link->nlink)
		link = link->nlink;
	return (link->nlink = new_reference(newentry), entry);
}

static t_symentry	*complete_entry(t_symentry *entry, t_symentry newentry)
{
	entry->defined = newentry.defined;
	entry->location = newentry.location;
	link = entry->flink;
	while (link)
	{
		ft_printf("label %ld referred at %ld\n", entry->location, link->location);
		link = link->nlink;
	}
	return (entry);
}

t_symentry	*symtable_enter(t_symtable *symtable, const char *name,
		t_symentry newentry)
{
	t_vec	*entries;
	t_symentry	*entry;
	
	entries = &symtable->entries;
	entry = symtable_find(symtable, name);
	if (!entry)
		return (enter_new(symtable, name, newentry);
	if (entry.defined)
		return (entry);
	if (!newentry.defined)
		return (add_reference(entry, newentry));
	return (complete_entry(entry, newentry));
}
