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

typedef enum s_actions
{
	ST_add,
	ST_subtract
}		t_actions;

typedef void	(*t_patch)(uint32_t mem[], uint32_t b, uint32_t v, t_actions a);

typedef struct s_forwardrefs
{
	uint32_t				byte;
	t_actions				action;
	struct s_forwardrefs	*nlink;
}				t_forwardrefs;

typedef struct s_entry
{
	t_alfa				name;
	uint32_t			value;
	bool				defined;
	t_forwardrefs		*flink;
}				t_entry;

typedef t_vec	t_symtable;

void	_symtable_findentry(t_symtable *symtable, char *name, bool *found);
void	symtable_print(t_symtable symtable);
void	symtable_enter(t_symtable *symtable, char *name, uint32_t value);
/*
void	symtable_valueof(t_symtable *symtable, char *name, uint32_t loc,
			uint32_t *value, t_actions action, bool *undefined);
			*/
void	symtable_outstandingrefs(t_symtable *symtable,
			uint32_t *mem, t_patch fix);

#endif
