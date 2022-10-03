/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/10/03 16:41:44 by jdavis           ###   ########.fr       */
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
		(*carriage)->tmp_pos = ((*carriage)->tmp_pos + move) % (MEM_SIZE - 1);
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
		ft_printf("BE   ZEROO\n");
		return (0);
	}
	if ((*carriage)->arg_types[first] == 1 && (info->operations[first][(*carriage)->statement_code - 1] == 1 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 4 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 5 \
	|| info->operations[first][(*carriage)->statement_code - 1] == 7))
	{
		//ft_printf("B   %d----------%d\n", core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		ft_printf("BE %i   %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		if (core[(*carriage)->tmp_pos] < 1 || core[(*carriage)->tmp_pos] > 16)
			return (-1);
		//make_move_tmp(carriage, 1);//moving and saving values before moves
		temp = core[(*carriage)->tmp_pos];
		make_move_tmp(carriage, 1);
		ft_printf("AF %i   %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
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
		ft_printf("BE  %i    %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		first = 0;
		while (i < type)// info->operations[SIZE][(*carriage)->statement_code - 1])
		{
			if ((*carriage)->tmp_pos + i < MEM_SIZE)
				hold = (*carriage)->tmp_pos + i;
			else
				hold = ((*carriage)->tmp_pos + i) % (MEM_SIZE - 1);
			hold = core[hold];
			//ft_printf("hold = %i\n", (hold / 16) * ft_pow(16, j));
			first += (hold / 16) * ft_pow(16, j--);
			hold %= 16;
			//ft_printf("hold = %i\n", (hold % 16) * ft_pow(16, j));
			first += (hold % 16) * ft_pow(16, j--);
			++i;
		}
		make_move_tmp(carriage, i);
		ft_printf("AF  %i %d----------%d\n", first, core[(*carriage)->tmp_pos], (*carriage)->tmp_pos);
		return (first);
	}
	return (-1);
}


static void	make_move(t_carriage **carriage, int move)
{
	if ((*carriage)->pos + move >= MEM_SIZE)
		(*carriage)->pos = ((*carriage)->pos + move) % (MEM_SIZE - 1);
	else
		(*carriage)->pos += move;
}

static void	move_carriage(t_info *info, t_carriage **carriage)
{
	int	i;

	i = 0;
	make_move(carriage, 2);
	while (i < 3)
	{
		if ((*carriage)->arg_types[i] == 1)
			make_move(carriage, 1);
		else if ((*carriage)->arg_types[i] == 3)
			make_move(carriage, 2);
		else if ((*carriage)->arg_types[i] == 2)
			make_move(carriage, info->operations[SIZE][(*carriage)->statement_code - 1]);
		++i;
	}
	(*carriage)->statement_code = 0;
}

static int	args_found_error(t_info *info, t_carriage **carriage)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((*carriage)->args_found[i] < 0)
		{
			move_carriage(info, carriage);
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

	ft_printf(" statement code   %i\n", core[(*carriage)->pos]);
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		//not sure if can just compare value of typecode element
		//is arguments arent valid or registry isnt valid, skip all of those bytes
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->tmp_pos = (*carriage)->pos;
		make_move_tmp(carriage, 1);
		ft_printf("typecode %i   pcb %i   pos %d\n", core[(*carriage)->pos + 1], info->operations[PCB][(*carriage)->statement_code - 1], (*carriage)->pos);
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
			//ft_printf("ARG TYPES %i  %i  %i\n", arg_found[ARG1],arg_found[ARG2],arg_found[ARG3]);
			ft_printf("TYPECODE %i   ARG TYPES %i  %i  %i\n",  core[((*carriage)->tmp_pos)], arg_found[ARG1],arg_found[ARG2],arg_found[ARG3]);
			(*carriage)->arg_types[ARG1] = arg_found[ARG1];
			(*carriage)->arg_types[ARG2] = arg_found[ARG2];
			(*carriage)->arg_types[ARG3] = arg_found[ARG3];
			make_move_tmp(carriage, 1);
			(*carriage)->args_found[ARG1] = first_arg(ARG1, carriage, info, core);
			(*carriage)->args_found[ARG2] = first_arg(ARG2, carriage, info, core);
			(*carriage)->args_found[ARG3] = first_arg(ARG3, carriage, info, core);
			//ft_printf("wait %i %lli\n", third_arg((u_int32_t)arg_found[ARG3], *carriage, info, core), (*carriage)->args_found[ARG3]);
			ft_printf("first = %i second %i  third %i\n", (*carriage)->args_found[ARG1], (*carriage)->args_found[ARG2], (*carriage)->args_found[ARG3]);
			if (args_found_error(info, carriage) == TRUE)
				return ;
		}
		else
		{
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->tmp_pos, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
			(*carriage)->args_found[ARG2] = 0;
			(*carriage)->args_found[ARG3] = 0;
		}
		op_table[(*carriage)->statement_code - 1](core, carriage, info);
		//ft_printf("SEGCHECK\n");
		move_carriage(info, carriage);
		//print_carriages(info);
		//print_core(core);
		//exit (0);
		// }
		// else
		// {
		// 	(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->tmp_pos, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
		// }
	}
	else
		make_move(carriage, 1);
	// {
	// 	if ((*carriage)->pos  == MEM_SIZE - 1)
	// 	{
	// 		(*carriage)->pos = 0;
	// 		(*carriage)->current  = &core[0];
	// 	}
	// 	else
	// 	{
	// 		(*carriage)->pos++;
	// 		(*carriage)->current++;
	// 	}
	// }
}

// static void	perform_statement_code(t_info *info)
// {
// 	perform_statement_code() and move carriage
// }

int	update_carriages(uint8_t core[MEM_SIZE], t_info *info, op_table *op_table[STATE])
{
	t_carriage	*carriage;

	carriage = info->head_carriage;
	while (carriage)
	{
		if (carriage->delay == 0)//means it moved last cycle or just been initiated
		{
			set_statement_code(core, &carriage, info);
			ft_printf("STATEMENT CODE-------------------\n");
		}
		if (carriage->delay > 0)
			carriage->delay -= 1;
		if (carriage->delay == 0)
		{
			//JEFF----------------
			//perform_statement_code() and move carriage
			// if cannot perform statement code move to next byte.
			perform_statement_code(core, &carriage, info, op_table);
		}
		carriage = carriage->next;
	}
	return (0);
}

/*

Couldn't get the void pointer thing to work so i changed it to uint32_t pointer instead.. if you can get the void pointer to work you can change it back if you want to

Page Virtual machine
Paragraf inside the cycle

Set statement code function:
- Read byte on which the carriage is located
- If number corresponds to operation code
	store operation code in the variable carriage->statement_code
	set carriage->delay == to number of cycles it would take to execute the statement_code

Perform statement code function:
- read and calculate pcb (binary stuff...) [https://glo.bi/corewar/]

update_carriages is called inside the file game_start.c

*/




/*


Operant function checks if it uses PCB
	if yes
		Function that checks PCB IF they are valid or not
			checks ARG1, ARG2, ARG3 if they are true
				if true collect ARG(function)
					collect and use (function specific to operand)
				else
					return error and skip specific amount (skip function)





*/