/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:11:44 by cchen             #+#    #+#             */
/*   Updated: 2022/10/07 11:39:39 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "definitions.h"
#include "symtable.h"

int	symtable_outstanding(t_symtable *symtable)
{
	size_t		index;
	size_t		count;
	t_symentry	*entry;

	count = 0;
	index = 0;
	while (index < symtable->entries.len)
	{
		entry = (t_symentry *) vec_get(&symtable->entries, index++);
		if (!entry->defined)
			++count;
	}
	if (count == 1)
		return (error_ret(SYMTABLE_OUTSTANDING));
	if (count > 1)
		return (error_ret(SYMTABLE_MULT_OUT));
	return (OK);
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

int	symtable_add(t_symtable *symtable, const char *name,
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

bool	symtable_is_defined(t_symtable *symtable, const char *name)
{
	t_symentry	*entry;

	entry = symtable_find(symtable, name);
	return (entry && entry->defined);
}
