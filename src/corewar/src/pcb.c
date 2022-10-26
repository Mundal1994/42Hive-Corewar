/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:24:40 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/18 15:32:36 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Resetting arguments collecting arrays	*/
void	reset_args(t_carriage **carriage)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		(*carriage)->arg_types[i] = 0;
		(*carriage)->args_found[i] = 0;
		++i;
	}
}

/*	Searching for any errors with the args found using the typecode	*/
static int	args_found_error(uint8_t core[MEM_SIZE], t_info *info, \
	t_carriage **carriage)
{
	int	i;
	int	total;
	int	prev;

	i = 0;
	while (i < 3)
	{
		if ((*carriage)->args_found[i] < 0)
		{
			total = 0;
			prev = (*carriage)->pos;
			move_carriage(carriage, &total);
			if ((info->flag[V_FLAG] & 16) == 16 && info->flag[V_FLAG] > 0)
				print_flag16(core, carriage, total, prev);
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

/*	Collecting args for statement using type codes	*/
int	pcb_true(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	u_int8_t	arg_found[ARGS];
	int			i;

	i = 0;
	while (i < ARGS)
		arg_found[i++] = core[((*carriage)->tmp_pos)];
	arg_found[ARG1] = arg_found[ARG1] >> 6;
	arg_found[ARG2] = arg_found[ARG2] << 2;
	arg_found[ARG2] = arg_found[ARG2] >> 6;
	arg_found[ARG3] = arg_found[ARG3] << 4;
	arg_found[ARG3] = arg_found[ARG3] >> 6;
	(*carriage)->arg_types[ARG1] = arg_found[ARG1];
	(*carriage)->arg_types[ARG2] = arg_found[ARG2];
	(*carriage)->arg_types[ARG3] = arg_found[ARG3];
	make_move_tmp(carriage, 1);
	(*carriage)->args_found[ARG1] = read_args(ARG1, carriage, core);
	(*carriage)->args_found[ARG2] = read_args(ARG2, carriage, core);
	(*carriage)->args_found[ARG3] = read_args(ARG3, carriage, core);
	return (args_found_error(core, info, carriage));
}

/*	COllecting values for functions not using typecodes	*/
void	pcb_false(uint8_t core[MEM_SIZE], t_carriage **carriage)
{
	if ((*carriage)->statement_code == 16)
	{
		(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->tmp_pos, \
			core, 1);
		(*carriage)->arg_types[ARG1] = R;
		if ((*carriage)->statement_code == 16 && ((*carriage)->args_found[ARG1] \
			< 1 || (*carriage)->args_found[ARG1] > 16))
			(*carriage)->args_found[ARG1] = -1;
	}
	else
	{
		(*carriage)->arg_types[ARG1] = D;
		(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->tmp_pos, \
			core, g_operations[SIZE][(*carriage)->statement_code - 1]);
	}
	(*carriage)->arg_types[ARG2] = 0;
	(*carriage)->arg_types[ARG3] = 0;
	(*carriage)->args_found[ARG2] = 0;
	(*carriage)->args_found[ARG3] = 0;
}
