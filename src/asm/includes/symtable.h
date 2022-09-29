/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:02:10 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/26 09:06:33 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTABLE_H
# define SYMTABLE_H

# include <stdbool.h>

# define HASH_INIT_SIZE 128

typedef enum s_actions
{
	ST_add,
	ST_subtract
}		t_actions;

typedef struct s_forwardrefs
{
	uint32_t				byte;
	t_actions				action;
	struct s_forwardrefs	*nlink;
}				t_forwardrefs;

typedef struct s_entry
{
	bool				defined;
	uint32_t			location;
	t_forwardrefs		*flink;
}				t_entry;


typedef struct	s_symtable
{
	t_hashmap	map;
	t_vec		entries;
	t_vec		forwardrefs;
}

/*
void	_symtable_findentry(t_symtable *symtable, char *name, bool *found);
void	symtable_print(t_symtable symtable);
void	symtable_enter(t_symtable *symtable, char *name, uint32_t value);
void	symtable_outstandingrefs(t_symtable *symtable,
			uint32_t *mem, t_patch fix);
			*/

#endif
