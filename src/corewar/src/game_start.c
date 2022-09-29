/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/09/28 17:38:24 by jdavis           ###   ########.fr       */
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

static void	check_carriage_live_call(t_info *info)
{
	t_carriage	*carriage;
	t_carriage	*next;
	int			limit;
	
	carriage = info->head_carriage;
	limit = info->total_cycles - info->cycles_to_die;
	while (carriage)
	{
		if (carriage->last_live_call <= limit)
		{
			next = carriage->next;
			delete_carriage(info, carriage->id);
			carriage = next;
		}
		else
			carriage = carriage->next;
	}
}

static void	kill_carriages(t_info *info)
{
	check_carriage_live_call(info);
	if (info->live_statement >= NBR_LIVE)
	{
		info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
		info->checks_count = 1;//unsure about corellation of max_checks and checks_count....
	}
	else
	{
		//unsure if this is how it is supposed to be
		info->checks_count += 1;//unsure about corellation of max_checks and checks_count....
		if (info->checks_count >= MAX_CHECKS)
			info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
	}
	info->cycle_count = info->cycles_to_die;
}

static void	check(t_info *info)
{
	info->cycle_count -= 1;
	info->total_cycles += 1;
	if (info->cycle_count <= 0)
		kill_carriages(info);
	info->live_statement = 0;
}

// static int	copy_carriage(t_info **info, t_carriage *carriage)
// {
// 	t_carriage	*new;
// 	int			i;

// 	new = (t_carriage *)malloc(sizeof(t_carriage));
// 	if (!new)
// 		return (ERROR);
// 	(*info)->carriage_count++;
// 	new->id = (*info)->carriage_count;
// 	new->carry = carriage->carry;
// 	new->statement_code = carriage->statement_code;
// 	new->last_live_call = carriage->last_live_call;
// 	new->delay = carriage->delay;//does this also have to be copied or should it be 0?
// 	new->pos = carriage->pos;//this should probably be different
// 	new->home = carriage->home;//this should probably be different
// 	new->current = carriage->current;//this should probably be different
// 	new->skip = carriage->skip;//this should probably be different
// 	i = 0;
// 	new->registry[i] = carriage->registry[i];
// 	// reg_1 = - player_id	NEEDS TO STILL FIX LOGIC OF THE REGISTRYS
// 	/*
// 	r1 == registry[0]
// 	r2 == registry[1]
// 	*/
// 	while (++i < REG_NUMBER)
// 		new->registry[i] = carriage->registry[i];
// 	new->next = (*info)->head_carriage;
// 	(*info)->head_carriage = new;
// 	return (0);
// }

int	game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ)//add player struct
{
	print_core(core);
	introduce_contestants(champ);//add player struct
	while (!one_carriage_left(info))
	{
		if (update_carriages(core, info) == ERROR)
			return (ERROR);
		check(info);
	}
	// TESTING FUNCTION TO BE ABLE TO COPY CARRIAGES and printing them
	// t_carriage *carriage;
	// carriage = info->head_carriage;
	// if (copy_carriage(&info, carriage) == ERROR)
	// 	return (ERROR);
	// print_carriages(info);
	announce_winner(champ, info->winner);
	return (0);
}
