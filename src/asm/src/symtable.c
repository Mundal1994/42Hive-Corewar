/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:09:54 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/10 14:17:57 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** *
 * Symtable is used to maintain a list of forward references in the source.
 *
 * There will be instances in the source code, where a reference to a label
 * appears before the label itself is defined. The parser will need to convert
 * the label reference to the correct position in memory, but will only be
 * able to do so once the location of the label is known.
 *
 * The symbol table solves this problem by maintaining a list of label entries.
 * Within each entry is also a linked list of forward references (t_forwardrefs)
 * which maintain the index position of the statement and argument number that
 * the reference appears in. 
 *
 * Updating the symbol table is managed by parser_update_symtable.c
 * ************************************************************************* */

#include "definitions.h"
#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

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
