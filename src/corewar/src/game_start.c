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

static void	introduce_contestants(void)//add player struct
{
	ft_printf("Introducing contestants...\n");
	// while (players)
	// {
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", 1, 23, "zork", "I'M ALIIIIVE");
	// }
}

int	game_start(uint32_t core[MEM_SIZE], t_info *info)//add player struct
{
	int i = 0;

	introduce_contestants();//add player struct
	while (!one_carriage_left(info))
	{
		if (update_carriages(info) == ERROR)
			return (ERROR);
		check(info);
		++i;
	}
	//print_core(core);
	ft_printf("Contestant %d, \"name of winner\", has won !\n", info->winner);
	if (core)
		i++;
	return (0);
}
