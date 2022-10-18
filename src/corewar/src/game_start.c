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

/*
checks how many carriages are left.
It will return FALSE if there are more than one carriage
otherwise it will return TRUE
*/
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

/*	frees carriages both in case of error and when ending the game/program	*/
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

/*
checks if we have a flag where we need to stop the game to show current
progress on standard output
*/
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

/*
prints current progress of the game to standard output and returns from game
*/
static int	print_dump_flags(uint8_t core[MEM_SIZE], t_info *info)
{
	print_core(core, info);
	if (info->flag[DI_FLAG] >= 0)
		print_info(info);
	if (info->flag[C_FLAG] >= 0)
		print_carriages(info);
	free_carriage(info);
	return (-1);
}

/*
begins the game by introducing the contestants
while loop initiated that will keep updating the carriages and deleting them
until one or no carriages are left
it will at the end announce the winner and end the game
*/
int	game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ)
{
	int	dump;

	introduce_contestants(champ);
	dump = flag_check(info);
	if (dump == 0)
		return (print_dump_flags(core, info));
	while (!one_carriage_left(info))
	{
		if ((info->flag[V_FLAG] & 2) == 2 && info->flag[V_FLAG] > 0)
			ft_printf("It is now cycle %d\n", info->total_cycles);
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
