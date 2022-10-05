/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/10/03 16:57:59 by jdavis           ###   ########.fr       */
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
	if (count == 1)
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

int	game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ)
{
	op_table	*op_table[STATE];// = {live, ld, st, add, sub, and, or, xor, zjmp, ldi, sti, fork_op, lld, lldi, lfork, aff,};

	init_op_table(op_table);
	introduce_contestants(champ);//add player struct
	int i = 0;
	while (!one_carriage_left(info))
	{
		if (update_carriages(core, info, op_table) == ERROR)
			return (ERROR);
		ft_printf("INSIDE LOOP--------------------\n");
		print_core(core);
		print_carriages(info);
		print_info(info);
		if (i++ > 200)
			break ;
		check(info);
	}
	announce_winner(champ, info->winner);
	return (0);
}
