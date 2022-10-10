/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/10/03 16:50:16 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	set_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	//logic of how to check if it is a possible operation command? just check if it is less than 16
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->delay = (u_int32_t)info->operations[DELAY][core[(*carriage)->pos] - 1];//needs to be -1 as our array is zero indexed
	}
	else
	{
		//In this case, it is necessary to remember the read code, and leave the value of the variable storing the number of cycles before execution equal to zero.
		//not sure about above statement
		(*carriage)->delay = 0;
	}
}
// static int	collect_arg(int arg, u_int8_t *core[MEM_SIZE], t_carriage **carriage, int state)
// {
// 	int	hold;

// 	if (arg == 1)
// 	{
// 		if ((*core) < 1 || (*core) > 16)
// 			return (-1);
// 		return (*core);
// 	}
// 	else if (arg == 2)
// 	{
		
// 	}
// 	else if (arg == 3)
// 	{

// 	}
// }

static void	make_move_tmp(t_carriage **carriage, int move)
{
	if ((*carriage)->tmp_pos + move >= MEM_SIZE)
	{
		(*carriage)->tmp_pos = ((*carriage)->tmp_pos + move) % MEM_SIZE;
	}
	else
		(*carriage)->tmp_pos += move;
}

static int64_t	first_arg(u_int32_t first, t_carriage **carriage, t_info *info, u_int8_t core[MEM_SIZE])
{
	int	hold;
	int	i;
	int	j;
	int	type;
	int	temp;
	//int	move;

	if (info->operations[first][(*carriage)->statement_code - 1] == 0)
	{
		//ft_printf("BE   ZEROO\n");
		return (0);
	}
	if ((*carriage)->arg_types[first] == 1 && (info->operations[first][(*carriage)->statement_code - 1] == 1 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 4 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 5 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 7))
	{
		//ft_printf("B   %d----------%d\n", core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		//ft_printf("BE %i   %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		if (core[(*carriage)->tmp_pos] < 1 || core[(*carriage)->tmp_pos] > 16)
			return (-1);
		//make_move_tmp(carriage, 1);//moving and saving values before moves
		temp = core[(*carriage)->tmp_pos];
		make_move_tmp(carriage, 1);
		//ft_printf("AF %i   %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		return (temp);
	}
	else if (((*carriage)->arg_types[first] == 2 && (info->operations[first][(*carriage)->statement_code - 1] == 2 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 4 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 6 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 7)) \
	|| ((*carriage)->arg_types[first] == 3 && (info->operations[first][(*carriage)->statement_code - 1] == 3 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 5 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 6 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 7)))
	{
		i = 0;
		if ((*carriage)->arg_types[first] == 2)
		{
			type = info->operations[SIZE][(*carriage)->statement_code - 1];
			j = (info->operations[SIZE][(*carriage)->statement_code - 1] * 2) - 1;
		}
		else
		{
			type = 2;
			j = 3;
		}
		//++(*carriage)->tmp_pos;
		//ft_printf("BE  %i    %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		first = 0;
		while (i < type)// info->operations[SIZE][(*carriage)->statement_code - 1])
		{
			if ((*carriage)->tmp_pos + i < MEM_SIZE)
				hold = (*carriage)->tmp_pos + i;
			else
				hold = ((*carriage)->tmp_pos + i) % MEM_SIZE;
			hold = core[hold];
			//ft_printf("hold = %i\n", (hold / 16) * ft_pow(16, j));
			first += (hold / 16) * ft_pow(16, j--);
			hold %= 16;
			//ft_printf("hold = %i\n", (hold % 16) * ft_pow(16, j));
			first += (hold % 16) * ft_pow(16, j--);
			++i;
		}
		make_move_tmp(carriage, i);
		//ft_printf("AF  %i %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		return (first);
	}
	return (-1);
}


static void	make_move(t_carriage **carriage, int move, int *total)
{
	// if ((*carriage)->id == 13)
	// 	ft_printf("pos %i    moves %i\n", (*carriage)->pos, move);
	if ((*carriage)->pos + move >= MEM_SIZE)
		(*carriage)->pos = ((*carriage)->pos + move) % MEM_SIZE;
	else
		(*carriage)->pos += move;
	*total += move;
}

static void	move_carriage(t_info *info, t_carriage **carriage, int *total)
{
	int	i;

	i = 0;
	// if ((*carriage)->id == 13)
	// ft_printf("Begin\n");

	if (info->operations[PCB][(*carriage)->statement_code - 1] == TRUE)
		make_move(carriage, 2, total);
	else
		make_move(carriage, 1, total);
	while (i < 3)
	{
		//ft_printf("%d	", (*carriage)->arg_types[i]);
		if ((*carriage)->arg_types[i] == 1)
			make_move(carriage, 1, total);
		else if ((*carriage)->arg_types[i] == 3)
			make_move(carriage, 2, total);
		else if ((*carriage)->arg_types[i] == 2)
			make_move(carriage, info->operations[SIZE][(*carriage)->statement_code - 1], total);
		++i;
	}
	// if ((*carriage)->id == 13)
	// {
	// 	ft_printf("End\n");
	// }
}

static void	print_flag16(uint8_t core[MEM_SIZE], t_carriage **carriage, int total, int prev)
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
	total = 0;
	while (i < 3)
	{
		if ((*carriage)->args_found[i] < 0)
		{
			prev = (*carriage)->pos;
			move_carriage(info, carriage, &total);
			if (info->flag[V_FLAG] == 16)
				print_flag16(core, carriage, total, prev);
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

void perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, op_table *op_table[STATE])
{
	u_int8_t			arg_found[ARGS];
	int					i;

	//ft_printf("\nCARRIAGE NBR: %d\n", (*carriage)->id);
	//ft_printf(" statement code   %i    pos %i\n", core[(*carriage)->pos], (*carriage)->pos);
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16\
		 && core[(*carriage)->pos] == (*carriage)->statement_code)
	{
		// if ((*carriage)->id == 13)
		// {
		// 	ft_printf("\nCARRIAGE NBR: %d\n", (*carriage)->id);
		// 	ft_printf(" statement code   %i    pos %i\n", core[(*carriage)->pos], (*carriage)->pos);
		// 	ft_printf("reg[%d]: %d\n", 2, (*carriage)->registry[2 - 1]);
		// 	if ((*carriage)->registry[2 - 1] != 0)
		// 		exit(0);
		// }
		//not sure if can just compare value of typecode element
		//is arguments arent valid or registry isnt valid, skip all of those bytes
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->tmp_pos = (*carriage)->pos;
		make_move_tmp(carriage, 1);
		// if ((*carriage)->id == 13)
		// 	ft_printf("typecode %i   pcb %i   pos %d\n", core[(*carriage)->pos + 1], info->operations[PCB][(*carriage)->statement_code - 1], (*carriage)->pos);
		if (info->operations[PCB][(*carriage)->statement_code - 1] == 1) //statements using typecode
		{
			i = 0;
			while (i < ARGS)
				arg_found[i++] = core[((*carriage)->tmp_pos)];
			arg_found[ARG1] = arg_found[ARG1] >> 6; 
			arg_found[ARG2] = arg_found[ARG2] << 2;
			arg_found[ARG2] = arg_found[ARG2] >> 6;
			arg_found[ARG3] = arg_found[ARG3] << 4;
			arg_found[ARG3] = arg_found[ARG3] >> 6;
			// if ((*carriage)->id == 13)
			// {
			// 	ft_printf("ARG TYPES %i  %i  %i\n", arg_found[ARG1],arg_found[ARG2],arg_found[ARG3]);
			// 	ft_printf("TYPECODE %i   ARG TYPES %i  %i  %i\n",  core[((*carriage)->tmp_pos)], arg_found[ARG1],arg_found[ARG2],arg_found[ARG3]);
			// }
			(*carriage)->arg_types[ARG1] = arg_found[ARG1];
			(*carriage)->arg_types[ARG2] = arg_found[ARG2];
			(*carriage)->arg_types[ARG3] = arg_found[ARG3];
			make_move_tmp(carriage, 1);
			(*carriage)->args_found[ARG1] = first_arg(ARG1, carriage, info, core);
			(*carriage)->args_found[ARG2] = first_arg(ARG2, carriage, info, core);
			(*carriage)->args_found[ARG3] = first_arg(ARG3, carriage, info, core);
			//ft_printf("wait %i %lli\n", third_arg((u_int32_t)arg_found[ARG3], *carriage, info, core), (*carriage)->args_found[ARG3]);
			// if ((*carriage)->id == 13)
			// {
			// 	ft_printf("first = %i second %i  third %i\n", (*carriage)->args_found[ARG1], (*carriage)->args_found[ARG2], (*carriage)->args_found[ARG3]);
			// 	if ((*carriage)->arg_types[ARG1] == 1)
			// 		ft_printf("reg[%d]: %d\n", (*carriage)->args_found[0], (*carriage)->registry[(*carriage)->args_found[0] - 1]);
			// }
			if (args_found_error(core, info, carriage) == TRUE)
				return ;
		}
		else
		{
			if ((*carriage)->statement_code == 16)
			{
				(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->tmp_pos, core, 1);
				(*carriage)->arg_types[ARG1] = R;
				if ((*carriage)->statement_code == 16 && ((*carriage)->args_found[ARG1] < 1 || (*carriage)->args_found[ARG1] > 16))
				{
					(*carriage)->args_found[ARG1] = -1;
				}
			}
			else
			{
				(*carriage)->arg_types[ARG1] = D;
				(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->tmp_pos, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
			}
			(*carriage)->args_found[ARG2] = 0;
			(*carriage)->args_found[ARG3] = 0;
		}
		op_table[(*carriage)->statement_code - 1](core, carriage, info);
		if ((*carriage)->statement_code != OP_ZJMP || ((*carriage)->statement_code == OP_ZJMP && !(*carriage)->carry))// added this statement
		{
			int	prev;
			int	total;
			prev = (*carriage)->pos;
			total = 0;
			move_carriage(info, carriage, &total);
			if (info->flag[V_FLAG] == 16)
				print_flag16(core, carriage, total, prev);
		}
		// if ((*carriage)->id == 13)
		// {
		// 	ft_printf("core[%d]: %d\n", (*carriage)->pos, core[(*carriage)->pos]);
		// 	print_core(core, info);
		// }
		(*carriage)->statement_code = 0;
		i = 0;
		while (i < 3)
		{
			(*carriage)->arg_types[i] = 0;
			(*carriage)->args_found[i] = 0;
			++i;
		}
	}
	else
	{
		int total = 0;
		make_move(carriage, 1, &total);
	}
	// if ((*carriage)->pos < 2000 && (*carriage)->registry[0] == 0)
	// {
	// 	print_core(core, info);
	// 	print_carriages(info);
	// 	print_info(info);
	// 	exit(0);
	// }
}

int	update_carriages(uint8_t core[MEM_SIZE], t_info *info, op_table *op_table[STATE])
{
	t_carriage	*carriage;

	carriage = info->head_carriage;
	while (carriage)
	{
		if (carriage->delay == 0)
		{
			set_statement_code(core, &carriage, info);
		}
		if (carriage->delay > 0)
			carriage->delay -= 1;
		if (carriage->delay == 0)
			perform_statement_code(core, &carriage, info, op_table);
		carriage = carriage->next;
	}
	return (0);
}
