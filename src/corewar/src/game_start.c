/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/10/05 10:45:46 by jdavis           ###   ########.fr       */
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

static void	init_op_table(op_table *op_table[STATE])
{
	int	i;

	i = 0;
	op_table[i++] = live;
	op_table[i++] = ld;
	op_table[i++] = st;
	op_table[i++] = add;
	op_table[i++] = sub;
	op_table[i++] = and;
	op_table[i++] = or;
	op_table[i++] = xor;
	op_table[i++] = zjmp;
	op_table[i++] = ldi;
	op_table[i++] = sti;
	op_table[i++] = fork_op;
	op_table[i++] = lld;
	op_table[i++] = lldi;
	op_table[i++] = lfork;
	op_table[i++] = aff;
}

static int	flag_check(t_info *info)
{
	int	i;

	i = 5;
	if (info->flag[1])
		return (info->flag[1]);
	while (i < FLAG_COUNT)
	{
		if (info->flag[i])
			return (info->flag[i]);
		++i;
	}
	return (-1);
}

int	game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ)
{
	op_table	*op_table[STATE];// = {live, ld, st, add, sub, and, or, xor, zjmp, ldi, sti, fork_op, lld, lldi, lfork, aff,};
	int			dump;

	init_op_table(op_table);
	introduce_contestants(champ);//add player struct
	dump = flag_check(info);
	while (!one_carriage_left(info))
	{
		//ft_printf("NEW CYCLE\n");
		if (print_cycle_count(info) == TRUE)
			ft_printf("It is now cycle %d\n", info->total_cycles);
		if (info->total_cycles == dump)//info->flag[D_FLAG] && info->total_cycles == info->flag[D_FLAG])
		{
			print_core(core, info);
			if (info->flag[DI_FLAG])
				print_info(info);
			if (info->flag[C_FLAG])
				print_carriages(info);
			exit(0);//need to make better exit code with freeing everything
		}
		if (update_carriages(core, info, op_table) == ERROR)
			return (ERROR);
		check(info);
	}
	announce_winner(champ, info->winner);
	return (0);
}
