/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/10/11 17:14:31 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	t_info *info)
{
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->delay = (u_int32_t)info->operations[DELAY]\
		[core[(*carriage)->pos] - 1];
	}
	else
	{
		(*carriage)->delay = 0;
	}
}

void	print_flag16(uint8_t core[MEM_SIZE], t_carriage **carriage, int total, int prev)
{
	int	i;

	ft_printf("ADV %d ", total);
	if (prev == 0)
		ft_printf("(0x0000 -> %#0.4x) ", (*carriage)->pos);
	else if ((*carriage)->pos == 0)
		ft_printf("(%#0.4x -> 0x0000) ", prev);
	else if (prev > (*carriage)->pos)
		ft_printf("(%#0.4x -> %#0.4x) ", prev, (*carriage)->pos + MEM_SIZE);
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

static int	args_found_error(uint8_t core[MEM_SIZE], t_info *info, t_carriage **carriage)
{
	int	i;
	int	total;
	int	prev;

	i = 0;
	while (i < 3)
	{
		//ft_printf("(*carriage)->args_found[i]: %d	", (*carriage)->args_found[i]);
		if ((*carriage)->args_found[i] < 0)
		{
			total = 0;
			prev = (*carriage)->pos;
			move_carriage(info, carriage, &total);
			if (info->flag[V_FLAG] >= 16 && info->flag[V_FLAG] <= 24)
			{
				//ft_printf("first %d", total);
				print_flag16(core, carriage, total, prev);
			}
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

static int	pcb_true(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	u_int8_t			arg_found[ARGS];
	int	i;

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
	(*carriage)->args_found[ARG1] = read_args(ARG1, carriage, info, core);
	(*carriage)->args_found[ARG2] = read_args(ARG2, carriage, info, core);
	(*carriage)->args_found[ARG3] = read_args(ARG3, carriage, info, core);
	return (args_found_error(core, info, carriage));
}

static void	pcb_false(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	t_info *info)
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
			core, info->operations[SIZE][(*carriage)->statement_code - 1]);
	}
	(*carriage)->args_found[ARG2] = 0;
	(*carriage)->args_found[ARG3] = 0;
}

void perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	t_info *info, op_table *op_table[STATE])
{
	int	prev;
	int	total;

	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16\
		 && core[(*carriage)->pos] == (*carriage)->statement_code)
	{
		//ft_printf("\nCARRIAGE NBR: %d\n", (*carriage)->id);
		//ft_printf(" statement code   %i    pos %i\n", core[(*carriage)->pos], (*carriage)->pos);
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->tmp_pos = (*carriage)->pos;
		make_move_tmp(carriage, 1);
		//ft_printf("typecode %i   pcb %i   pos %d\n", core[(*carriage)->pos + 1], info->operations[PCB][(*carriage)->statement_code - 1], (*carriage)->pos);
		if (info->operations[PCB][(*carriage)->statement_code - 1] == 1) //statements using typecode
		{
			if (pcb_true(core, carriage, info) == TRUE)
				return ;
		}
		else
			pcb_false(core, carriage, info);
		op_table[(*carriage)->statement_code - 1](core, carriage, info);
		if ((*carriage)->statement_code != OP_ZJMP || ((*carriage)->statement_code == \
			OP_ZJMP && !(*carriage)->carry))
		{
			prev = (*carriage)->pos;
			total = 0;
			move_carriage(info, carriage, &total);
			if (info->flag[V_FLAG] >= 16 && info->flag[V_FLAG] <= 24)
			{
				print_flag16(core, carriage, total, prev);
			}
		}
	}
	else
	{
		if ((*carriage)->statement_code >= 1 && (*carriage)->statement_code <= 16)// && (*carriage)->statement_code != OP_ZJMP)
		{
			prev = (*carriage)->pos;
			total = 0;
			if (info->operations[PCB][(*carriage)->statement_code - 1] == 1)
				make_move(carriage, 2, &total);
			else
				make_move(carriage, info->operations[SIZE][(*carriage)->statement_code - 1] + 1, &total);
			if (info->flag[V_FLAG] >= 16 && info->flag[V_FLAG] <= 24)
			{
				//ft_printf("second %d ", (*carriage)->statement_code);
				print_flag16(core, carriage, total, prev);
			}
		}
		else
		{
			make_move(carriage, 1, &total);
		}
	}
	reset_args(carriage);
}

int	update_carriages(uint8_t core[MEM_SIZE], t_info *info, \
	op_table *op_table[STATE])
{
	t_carriage	*carriage;

	carriage = info->head_carriage;
	while (carriage)
	{
		if (carriage->delay == 0)
		{
			set_statement_code(core, &carriage, info);
			//if (carriage->id == 1)// && info->total_cycles > 19130 && info->total_cycles < 20000)
			//	ft_printf("statecode: carriage %d statement_code: %d	carry: %d	delay: %d	total_cycles: %d\n", carriage->id, carriage->statement_code, carriage->carry, carriage->delay, info->total_cycles);
		}
		if (carriage->delay > 0)
			carriage->delay -= 1;
		if (carriage->delay == 0)
		{
			perform_statement_code(core, &carriage, info, op_table);
			// if (carriage->id == 1)// && info->total_cycles > 19130 && info->total_cycles < 20000)
			// 	ft_printf("performed: carriage %d statement_code: %d	carry: %d	delay: %d	total_cycles: %d	r0: %d\n", carriage->id, carriage->statement_code, carriage->carry, carriage->delay, info->total_cycles, carriage->registry[0]);
			carriage->statement_code = OP_NULL;
		}
		carriage = carriage->next;
	}
	return (0);
}


/*
./test_v_flag.sh ../../../vm_champs/corewar ./corewar champs/examples/zork.cor champs/examples/jinx.cor

*/