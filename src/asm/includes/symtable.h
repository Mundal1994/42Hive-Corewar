/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:02:10 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/07 11:09:45 by caruychen        ###   ########.fr       */
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

#ifndef SYMTABLE_H
# define SYMTABLE_H

# include "vec.h"
# include "hashmap.h"
# include <stdbool.h>
# include <stdint.h>

typedef struct s_forwardrefs
{
	size_t					statement_id;
	uint8_t					arg;
	struct s_forwardrefs	*nlink;
}				t_forwardrefs;

typedef struct s_symentry
{
	bool				defined;
	size_t				statement_id;
	uint8_t				arg;
	uint32_t			location;
	t_forwardrefs		*flink;
}				t_symentry;

typedef struct s_symtable
{
	t_hashmap	map;
	t_vec		entries;
}			t_symtable;

int			symtable_init(t_symtable *symtable);
void		symtable_free(t_symtable *symtable);
int			symtable_outstanding(t_symtable *symtable);
t_symentry	*symtable_find(t_symtable *symtable, const char *name);
int			symtable_add(t_symtable *symtable, const char *name,
				t_symentry newentry);
bool		symtable_is_defined(t_symtable *symtable, const char *name);

#endif
