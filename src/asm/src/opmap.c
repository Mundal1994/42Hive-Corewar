/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:08:24 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 09:40:30 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[OP_NUMBER] = {
{"live", 1, {T_DIR}, 1, 0, 0},
{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 0},
{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 0},
{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 0},
{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 0},
{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 0},
{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 0},
{"zjmp", 1, {T_DIR}, 9, 0, 1},
{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 1},
{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 1},
{"fork", 1, {T_DIR}, 12, 0, 1},
{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 0},
{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 1},
{"lfork", 1, {T_DIR}, 15, 0, 1},
{"aff", 1, {T_REG}, 16, 1, 0},
};

int	opmap_new(t_hashmap *opmap)
{
	int	index;

	if (hashmap_new(opmap) == ERROR)
		return (perror("ERROR"), ERROR);
	index = 0;
	while (index < OP_NUMBER)
	{
		if (!hashmap_try_insert(opmap, g_op_tab[index].name, index))
			return (perror("ERROR"), ERROR);
		++index;
	}
	return (OK);
}

t_op	*opmap_get(t_hashmap *opmap, const char *key)
{
	int	*index;

	index = hashmap_get(opmap, key);
	if (!index)
		return (exit_error_str(ERR_MSG_NO_OP), NULL);
	if (*index < 0 || *index >= OP_NUMBER)
		return (exit_error_str(ERR_MSG_BAD_OP_IDX), NULL);
	return (&g_op_tab[*index]);
}

void	opmap_free(t_hashmap **opmap)
{
	hashmap_free(*opmap);
	*opmap = NULL;
}
