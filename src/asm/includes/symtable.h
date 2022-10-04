/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:02:10 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/04 10:59:21 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTABLE_H
# define SYMTABLE_H

# include "libft.h"
# include "definitions.h"
# include "errors.h"
# include <stdbool.h>
# include <stdint.h>

typedef struct s_forwardrefs
{
	t_arg			*arg;
	struct s_forwardrefs	*nlink;
}				t_forwardrefs;

typedef struct s_symentry
{
	bool				defined;
	t_arg				*arg;
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
t_symentry	*symtable_find(t_symtable *symtable, const char *name);
t_symentry	symtable_newentry(bool defined, t_arg *arg, uint32_t location);
int		symtable_enter(t_symtable *symtable, const char *name,
				t_symentry newentry);

#endif
