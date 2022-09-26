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

static void	introduce_contestants(t_profile **champ)//add player struct
{
	t_profile *head;

	ft_printf("Introducing contestants...\n");
	head = *champ;
	while (*champ)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", (*champ)->i, (*champ)->exec_cd_sz, (*champ)->name, (*champ)->comment);
		*champ = (*champ)->next;
	}
	*champ = head;
}

int	game_start(uint32_t core[MEM_SIZE], t_info *info, t_profile **champ)//add player struct
{
	int	i;

	//declare operation tabs if malloc error return ERROR
	introduce_contestants(champ);//add player struct
	while (!one_carriage_left(info))
	{
		if (update_carriages(info) == ERROR)
			return (ERROR);
		check(info);
	}
	//print_core(core);
	i = 0;
	while (*champ)
	{
		if (info->winner == (*champ)->i + 1)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", info->winner, (*champ)->name);
			break ;
		}
		(*champ)->next;
	}
	if (core)
		i++;
	return (0);
}
