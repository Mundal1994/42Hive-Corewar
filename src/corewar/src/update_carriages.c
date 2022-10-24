/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/10/18 15:22:41 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	sets the statement_code and delay	*/
void	set_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage)
{
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->delay = \
		(u_int32_t)g_operations[DELAY][core[(*carriage)->pos] - 1];
	}
	else
		(*carriage)->delay = 0;
}

/*	checks if the statecode uses or type code or not and executes according*/
static int	pcb(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	t_info *info)
{
	if (g_operations[PCB][(*carriage)->statement_code - 1] == 1)
	{
		if (pcb_true(core, carriage, info) == TRUE)
			return (1);
	}
	else
		pcb_false(core, carriage);
	return (0);
}

/*	performs the fubction related to the function code or error, and moves 
	carriage position
*/
void	perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	t_info *info)
{
	int	prev;
	int	total;

	if ((*carriage)->statement_code >= 1 && (*carriage)->statement_code <= 16)
	{
		(*carriage)->tmp_pos = (*carriage)->pos;
		make_move_tmp(carriage, 1);
		if (pcb(core, carriage, info))
			return ;
		g_op_table[(*carriage)->statement_code - 1](core, carriage, info);
		if ((*carriage)->statement_code != OP_ZJMP || \
			((*carriage)->statement_code == OP_ZJMP && !(*carriage)->carry))
		{
			prev = (*carriage)->pos;
			total = 0;
			move_carriage(carriage, &total);
			if ((info->flag[V_FLAG] & 16) == 16 && info->flag[V_FLAG] > 0)
				print_flag16(core, carriage, total, prev);
		}
	}
	else
		make_move(carriage, 1, &total);
	set_arg(carriage);
}

/*
goes through all the carriages and either updates the statement
code or delay time for executing a statement code
*/
int	update_carriages(uint8_t core[MEM_SIZE], t_info *info)
{
	t_carriage	*carriage;

	carriage = info->head_carriage;
	while (carriage)
	{
		if (carriage->delay == 0)
		{
			set_statement_code(core, &carriage);
		}
		if (carriage->delay > 0)
			carriage->delay -= 1;
		if (carriage->delay == 0)
		{
			perform_statement_code(core, &carriage, info);
			carriage->statement_code = OP_NULL;
		}
		carriage = carriage->next;
	}
	return (0);
}
