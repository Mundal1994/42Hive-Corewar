/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opmap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:05:33 by cchen             #+#    #+#             */
/*   Updated: 2022/10/10 14:06:42 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPMAP_H
# define OPMAP_H

# include <stdbool.h>
# include <stdint.h>
# include "op.h"
# include "hashmap.h"

typedef struct s_op
{
	char		*name;
	uint8_t		argc;
	t_arg_type	arg_types[3];
	uint8_t		opcode;
	bool		acb;
	bool		label;
}				t_op;

/* Opmap stores the opcodes to identify assembly instructions */
int			opmap_new(t_hashmap *opmap);
const t_op	*opmap_get(t_hashmap *opmap, const char *key);
void		opmap_free(t_hashmap *opmap);

#endif
