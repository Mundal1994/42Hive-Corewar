/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:57:51 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	one_carriage_left(t_info *info)
{
	t_carriage	*carriage;
	int			count;

	carriage = info->head_carriage;
	count = 0;
	while (carriage)
	{
		++count;
		carriage = carriage->next;
	}
	if (count <= 1)
		return (TRUE);
	return (FALSE);
}

// static void	init_op_table(op_table *op_table[STATE])
// {
// 	int	i;

// 	i = 0;
// 	op_table[i++] = op_live;
// 	op_table[i++] = op_ld;
// 	op_table[i++] = op_st;
// 	op_table[i++] = op_add;
// 	op_table[i++] = op_sub;
// 	op_table[i++] = op_and;
// 	op_table[i++] = op_or;
// 	op_table[i++] = op_xor;
// 	op_table[i++] = op_zjmp;
// 	op_table[i++] = op_ldi;
// 	op_table[i++] = op_sti;
// 	op_table[i++] = op_fork;
// 	op_table[i++] = op_lld;
// 	op_table[i++] = op_lldi;
// 	op_table[i++] = op_lfork;
// 	op_table[i++] = op_aff;
// }

int	free_carriage(t_info *info)
{
	t_carriage	*next;

	while (info->head_carriage)
	{
		next = info->head_carriage->next;
		free(info->head_carriage);
		info->head_carriage = next;
	}
	return (ERROR);
}

static int	flag_check(t_info *info)
{
	int	i;

	i = D_FLAG;
	while (i < FLAG_COUNT)
	{
		if (info->flag[i] >= 0)
			return (info->flag[i]);
		++i;
	}
	return (-1);
}

int	game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ)
{
	//op_table	*op_table[STATE];
	int			dump;

	//init_op_table(op_table);
	introduce_contestants(champ);
	dump = flag_check(info);
	if (dump == 0)
		return (print_dump_flags(core, info));
	while (!one_carriage_left(info))
	{
		print_cycle_count(info);
		if (update_carriages(core, info) == ERROR)//, op_table) == ERROR)
			return (free_carriage(info));
		if (info->total_cycles == dump)
			return (print_dump_flags(core, info));
		check(info);
	}
	if (info->flag[I_FLAG] == TRUE)
		print_info(info);
	free_carriage(info);
	announce_winner(champ, info->winner);
	return (0);
}
