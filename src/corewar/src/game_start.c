/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/09/23 12:33:18 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	one_carriage_left(t_info *info)
{
	t_carriage	*carriage;
	int			count;

	carriage = info->head;
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

static void	kill_carriages(t_info *info)
{
	//FUNCTION
	//function that checks all of the carriages and when their last live_call was and if it is within the limit
	if (info->live_statement >= NBR_LIVE)
	{
		info->cycle_of_death = info->cycle_of_death - CYCLE_DELTA;
		info->checks_count = 1;//unsure about corellation of max_checks and checks_count....
	}
	else
	{
		//unsure if this is how it is supposed to be
		info->checks_count += 1;//unsure about corellation of max_checks and checks_count....
		if (info->checks_count >= MAX_CHECKS)
			info->cycle_of_death = info->cycle_of_death - CYCLE_DELTA;
	}
	info->death_count = info->cycle_of_death;
}

static void	check(t_info *info)
{
	info->death_count -= 1;
	if (info->death_count <= 0)
		kill_carriages(info);
	info->total_cycles += 1;
	info->live_statement = 0;
}

/*
Introducing contestants...
* Player 1, weighing 23 bytes, "zork" ("I'M ALIIIIVE") !
* Player 2, weighing 394 bytes, "turtle" ("TURTLE FFS U LAMA") !
*/

static void	introduce_contestants(t_profile **champ, int total)//add player struct
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < total)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", champ[i]->i, 23, champ[i]->name, champ[i]->comment);
		++i;
	}
}

int	game_start(uint32_t core[MEM_SIZE], t_info *info, t_profile **champ, int total)//add player struct
{
	int	i;

	introduce_contestants(champ, total);//add player struct
	while (!one_carriage_left(info))
	{
		if (update_carriages(info) == ERROR)
			return (ERROR);
		check(info);
	}
	//print_core(core);
	i = 0;
	while (i < total)
	{
		if (info->winner == champ[i]->i)
		{
			ft_printf("Contestant %d, \"name of winner\", has won !\n", info->winner);
		}
		++i;
	}
	if (core)
		i++;
	return (0);
}
