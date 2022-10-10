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
