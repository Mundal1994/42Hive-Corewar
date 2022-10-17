/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:59 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:58:01 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	deletes the carriages in the struct regardless of location	*/
static void	delete_carriage(t_info *info, int id)
{
	t_carriage	*carriage;
	t_carriage	*prev;

	carriage = info->head_carriage;
	prev = NULL;
	while (carriage)
	{
		if (carriage->id == id)
		{
			if (!carriage->next && !prev)
				info->head_carriage = NULL;
			else if (!carriage->next)
				prev->next = NULL;
			else if (!prev)
				info->head_carriage = carriage->next;
			else
				prev->next = carriage->next;
			free(carriage);
			return ;
		}
		prev = carriage;
		carriage = carriage->next;
	}
}

/*
if flag -v 8 is activated the processes/carriage that has been killed
will be printed to standard output. It will also print how long carrriage
has been dead.
*/
static void	print_process_killed(t_info *info, t_carriage *carriage)
{
	if (info->cycles_to_die < 0)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
		carriage->id, info->total_cycles - carriage->last_live_call - 1, \
		info->cycles_to_die);
	else
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
		carriage->id, info->total_cycles - carriage->last_live_call - 1, \
		info->cycles_to_die);
}

/*
checks if the carriages last_live_call is within the limit
if one is not within the limit it will be removed from the linked list
*/
static void	check_carriage_live_call(t_info *info)
{
	t_carriage	*carriage;
	t_carriage	*next;
	int			limit;

	carriage = info->head_carriage;
	if (info->cycles_to_die < 0)
		limit = info->total_cycles - 1;
	else
		limit = info->total_cycles - info->cycles_to_die - 1;
	while (carriage)
	{
		if (carriage->last_live_call <= limit)
		{
			next = carriage->next;
			if ((info->flag[V_FLAG] & 8) == 8)
				print_process_killed(info, carriage);
			delete_carriage(info, carriage->id);
			carriage = next;
		}
		else
			carriage = carriage->next;
	}
}

/*
if flag -v 2 is activated it will print what cycle_to_die is currently on
*/
static void	flag_print_cycle_to_die(t_info *info)
{
	if ((info->flag[V_FLAG] & 2) == 2)
		ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
}

/*
check that happens every cycle. Increase total_cycle counter and if
the cycle count reached 0 we will also check the carriages last_live_call.
The cycle_to_die will be updated depending on how many live_statements
have been made in total. If it is below 21 cycle_to_die will stay the same,
if it is above we will reduce cycle_to_die by CYCLE_DELTA.
An additional way to reduce cycle_to_die is if checks_count reaches MAX_CHECKS
in that case we will reduce cycle_to_die as well.
*/
void	check(t_info *info)
{
	info->cycle_count -= 1;
	info->total_cycles += 1;
	if (info->cycle_count <= 0)
	{
		check_carriage_live_call(info);
		if (info->live_statement >= NBR_LIVE)
		{
			info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
			info->checks_count = 0;
			flag_print_cycle_to_die(info);
		}
		else
		{
			info->checks_count += 1;
			if (info->checks_count >= MAX_CHECKS)
			{
				info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
				info->checks_count = 0;
				flag_print_cycle_to_die(info);
			}
		}
		info->cycle_count = info->cycles_to_die;
		info->live_statement = 0;
	}
}
