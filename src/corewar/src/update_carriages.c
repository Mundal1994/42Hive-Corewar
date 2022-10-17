/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/10/11 17:24:23 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage)
{
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->delay = \
		(u_int32_t)g_operations[DELAY][core[(*carriage)->pos] - 1];
	}
	else
	{
		(*carriage)->delay = 0;
	}
}

void	print_flag16(uint8_t core[MEM_SIZE], t_carriage **carriage, \
int total, int prev)
{
	int	i;

	ft_printf("ADV %d ", total);
	if (prev == 0)
		ft_printf("(0x0000 -> %#0.4x) ", (*carriage)->pos);
	else if (prev > (*carriage)->pos)
		ft_printf("(%#0.4x -> %#0.4x) ", prev, (*carriage)->pos + MEM_SIZE);
	else if ((*carriage)->pos == 0)
		ft_printf("(%#0.4x -> 0x0000) ", prev);
	else
		ft_printf("(%#0.4x -> %#0.4x) ", prev, (*carriage)->pos);
	i = 0;
	while (i < total)
	{
		if (prev + i >= MEM_SIZE)
			prev = 0 - i;
		if (core[prev + i] < 16)
			ft_printf("0%x ", core[prev + i]);
		else
			ft_printf("%x ", core[prev + i]);
		++i;
	}
	ft_putchar('\n');
}

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
			if ((info->flag[V_FLAG] & 16) == 16)
				print_flag16(core, carriage, total, prev);
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

static void	reset_args(t_carriage **carriage)
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

static int	pcb_true(uint8_t core[MEM_SIZE], t_carriage **carriage, \
t_info *info)
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

static void	pcb_false(uint8_t core[MEM_SIZE], t_carriage **carriage)
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

void	perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	t_info *info)
{
	int	prev;
	int	total;

	if ((*carriage)->statement_code >= 1 && (*carriage)->statement_code <= 16)
	{
		(*carriage)->tmp_pos = (*carriage)->pos;
		make_move_tmp(carriage, 1);
		if (g_operations[PCB][(*carriage)->statement_code - 1] == 1)
		{
			if (pcb_true(core, carriage, info) == TRUE)
				return ;
		}
		else
			pcb_false(core, carriage);
		g_op_table[(*carriage)->statement_code - 1](core, carriage, info);
		if ((*carriage)->statement_code != OP_ZJMP || \
			((*carriage)->statement_code == OP_ZJMP && !(*carriage)->carry))
		{
			prev = (*carriage)->pos;
			total = 0;
			move_carriage(carriage, &total);
			if ((info->flag[V_FLAG] & 16) == 16)
				print_flag16(core, carriage, total, prev);
		}
	}
	else
		make_move(carriage, 1, &total);
	reset_args(carriage);
}

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
