/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcodes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:49:14 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 09:49:15 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[OP_NUMBER + 1] = {
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
{0, 0, {0}, 0, 0, 0}
};

int	opcodes_new_hashmap(t_hashmap *op_map, size_t capacity)
{
	if (hashmap_new_with_capacity(op_map, capacity) == ERROR)
		return (perror("ERROR"), ERROR);
}
