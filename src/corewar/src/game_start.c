/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/10/18 12:02:12 by jdavis           ###   ########.fr       */
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
	int	dump;

	introduce_contestants(champ);
	dump = flag_check(info);
	if (dump == 0)
		return (print_dump_flags(core, info));
	while (!one_carriage_left(info))
	{
		print_cycle_count(info, FALSE);
		if (update_carriages(core, info) == ERROR)
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
