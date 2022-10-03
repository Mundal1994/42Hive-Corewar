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

int	game_start(uint8_t core[MEM_SIZE], t_info *info, t_profile *champ)//add player struct
{
	op_table *op_table[STATE] = {
		live,
		ld,
		st,
		add,
		sub,
		and,
		or,
		xor,
		zjmp,
		ldi,
		sti,
		fork_op,
		lld,
		lldi,
		lfork,
		aff,
	};
	// int	args[ARGS];
	// print_core(core);
	// print_carriages(info);
	// print_info(info);
	// args[0] = -1;
	// live(&info->head_carriage->next, info);
	// args[0] = 2;
	// args[1] = 5;
	// info->head_carriage->arg_types[1] = R;
	// ld(core, &info->head_carriage, info);
	// args[0] = 0;
	// info->head_carriage->next->arg_types[1] = I;
	// ld(core, &info->head_carriage->next, info);
	// args[0] = 5;
	// args[1] = 50;
	// info->head_carriage->arg_types[1] = I;
	// st(core, &info->head_carriage, info);
	// args[0] = 4;
	// info->head_carriage->next->registry[4] = 4;
	// info->head_carriage->next->registry[3] = 3;
	// info->head_carriage->next->registry[5] = 5;
	// args[1] = 5;
	// info->head_carriage->next->arg_types[1] = R;
	// //st(args, core, &info->head_carriage->next, info);
	// ft_printf("--------SEE CHANGE---------\n");
	/*
	info->head_carriage->arg_types[0] = I;
	info->head_carriage->arg_types[1] = R;
	info->head_carriage->args_found[0] = 10;
	info->head_carriage->args_found[1] = 4;
	info->head_carriage->pos = MEM_SIZE - 2;
	op_table[1](core, &info->head_carriage, info);
	*/
	ft_printf("BEFORE LOOP--------------------\n");
	print_core(core);
	print_carriages(info);
	print_info(info);
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
		if (i++ > 1)
			break ;
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
