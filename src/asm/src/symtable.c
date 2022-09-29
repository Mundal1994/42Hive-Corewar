/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:09:54 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/29 17:48:10 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtable.h"

int	symtable_init(t_symtable *symtable)
{
	if (hashmap_new(&symtable->map) == ERROR)
		return (perror("SYSTEM ERROR:"), ERROR);
	if (vec_new(&symtable->entries, 1, sizeof(t_symentry)) == ERROR)
	{
		hashmap_free(&symtable->map);
		return (perror("SYSTEM ERROR:"), ERROR);
	}
	return (OK);
}

static void	symtable_freerefs(t_forwardrefs **link)
{
	if (!*link)
		return ;
	symtable_freerefs(&(*link)->nlink);
	free(*link);
	*link = NULL;
}

void	symtable_free(t_symtable *symtable)
{
	size_t		index;
	t_vec		*entries;
	t_symentry	*entry;

	hashmap_free(&symtable->map);
	entries = &symtable->entries;
	index = 0;
	while (index < entries->len)
	{
		entry = (t_symentry *) vec_get(entries, index++);
		symtable_freerefs(&entry->flink);
	}
	vec_free(entries);
}

t_symentry	*symtable_find(t_symtable *symtable, const char *name)
{
	t_entry	*entry;
	size_t	value;

	entry = hashmap_entry(&symtable->map, name);
	if (!entry || entry->value < 0)
		return (NULL);
	value = (size_t) entry->value;
	return ((t_symentry *) vec_get(&symtable->entries, value));
}
