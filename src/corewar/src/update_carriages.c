/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/09/30 11:20:27 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	set_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	//logic of how to check if it is a possible operation command? just check if it is less than 16
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		(*carriage)->statement_code = core[(*carriage)->pos];
		(*carriage)->delay = (u_int32_t)info->operations[DELAY][core[(*carriage)->pos]];
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
static int64_t	first_arg(u_int32_t first, t_carriage *carriage, t_info *info, u_int8_t core[MEM_SIZE])
{
	int	hold;
	int	i;
	int	j;
	int	type;

	if (first == 1 && (info->operations[ARG1][carriage->statement_code - 1] == 1 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 4 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 5 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 7))
	{

		if (core[carriage->tmp_pos + 1] < 1 || core[carriage->tmp_pos + 1] > 16)
			return (-1);
		return (core[++carriage->tmp_pos]);
	}
	else if ((first == 2 && (info->operations[ARG1][carriage->statement_code - 1] == 2 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 4 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 6 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 7)) \
	|| (first == 3 && (info->operations[ARG1][carriage->statement_code - 1] == 3 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 5 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 6 \
	|| info->operations[ARG1][carriage->statement_code - 1] == 7)))
	{
		i = 0;
		if (first == 2)
		{
			type = info->operations[SIZE][carriage->statement_code - 1];
			j = (info->operations[SIZE][carriage->statement_code - 1] * 2) - 1;
		}
		else
		{
			type = 2;
			j = 3;
		}
		++carriage->tmp_pos;
		first = 0;
		while (i < type)// info->operations[SIZE][carriage->statement_code - 1])
		{
			hold = core[carriage->tmp_pos + i];
			first += (hold / 16) * ft_pow(16, j--);
			hold %= 16;
			first += (hold / 16) * ft_pow(16, j--);
			++i;
		}
		carriage->tmp_pos += i;
		return (first);
	}
	return (-1);
}

static int64_t	second_arg(u_int32_t second, t_carriage *carriage, t_info *info, u_int8_t core[MEM_SIZE])
{
	int	i;
	int	j;
	int	hold;
	int	type;

	if (info->operations[ARG2][carriage->statement_code - 1] == 0)
	{
		return (0);
	}
	else if (second == 1 && (info->operations[ARG2][carriage->statement_code - 1] == 1 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 4 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 5 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 7))
	{

		if (core[carriage->tmp_pos + 1] < 1 || core[carriage->tmp_pos + 1] > 16)
		{
			return (-1);
		}
		return (core[++carriage->tmp_pos]);
	}
	else if ((second == 2 && (info->operations[ARG2][carriage->statement_code - 1] == 2 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 4 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 6 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 7)) \
	|| (second == 3 && (info->operations[ARG2][carriage->statement_code - 1] == 3 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 5 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 6 \
	|| info->operations[ARG2][carriage->statement_code - 1] == 7)))
	{
		i = 0;
		if (second == 2)
		{
			type = info->operations[SIZE][carriage->statement_code - 1];
			j = (info->operations[SIZE][carriage->statement_code - 1] * 2) - 1;
		}
		else
		{
			type = 2;
			j = 3;
		}
		++carriage->tmp_pos;
		second = 0;
		while (i < type)//info->operations[SIZE][carriage->statement_code - 1])
		{
			hold = core[carriage->tmp_pos + i];
			second += (hold / 16) * ft_pow(16, j--);
			hold %= 16;
			second += (hold % 16) * ft_pow(16, j--);
			++i;
		}
		carriage->tmp_pos += i;
		return (second);
	}
	return (-1);
}

static int64_t	third_arg(u_int32_t third, t_carriage *carriage, t_info *info, u_int8_t core[MEM_SIZE])
{
	int	i;
	int	j;
	int	hold;
	int	type;

	if (info->operations[ARG3][carriage->statement_code - 1] == 0)
	{
		return (0);
	}
	else if (third == 1 && (info->operations[ARG3][carriage->statement_code - 1] == 1 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 4 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 5 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 7))
	{
		//ft_printf("HERE\n");
		if (core[carriage->tmp_pos + 1] < 1 || core[carriage->tmp_pos + 1] > 16)
		{
			ft_printf("HERETOO\n");
			return (-1);
		}
		return (core[++carriage->tmp_pos]);
	}
	else if ((third == 2 && (info->operations[ARG3][carriage->statement_code - 1] == 2 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 4 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 6 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 7)) \
	|| (third == 3 && (info->operations[ARG3][carriage->statement_code - 1] == 3 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 5 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 6 \
	|| info->operations[ARG3][carriage->statement_code - 1] == 7)))
	{
		i = 0;
		if (third == 2)
		{
			type = info->operations[SIZE][carriage->statement_code - 1];
			j = (info->operations[SIZE][carriage->statement_code - 1] * 2) - 1;
		}
		else
		{
			type = 2;
			j = 3;
		}
		++carriage->tmp_pos;
		third = 0;
		while (i < type)//info->operations[SIZE][carriage->statement_code - 1])
		{
			hold = core[carriage->tmp_pos + i];
			third += (hold / 16) * ft_pow(16, j--);
			hold %= 16;
			third += (hold % 16) * ft_pow(16, j--);
			++i;
		}
		carriage->tmp_pos += i;
		return (third);
	}
	return (-1);
}

void perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, op_table *op_table[STATE])
{
	//u_int8_t	compare;
	//u_int8_t			first;
	u_int8_t			arg_found[ARGS];
	//u_int8_t		third;
	//u_int8_t			forth;
	int					i;
	//int			tmp_pos;

	ft_printf(" statement code   %i\n", core[(*carriage)->pos]);
	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		//not sure if can just compare value of typecode element
		//is arguments arent valid or registry isnt valid, skip all of those bytes
		(*carriage)->statement_code = core[(*carriage)->pos];
		ft_printf("typecode %i   pcb %i\n", core[(*carriage)->pos + 1], info->operations[PCB][core[(*carriage)->pos] - 1]);
		if (info->operations[PCB][core[(*carriage)->pos] - 1] == 1) //statements using typecode
		{
			//exit (0);
			if ((*carriage)->pos + 1 <= MEM_SIZE - 1)
				(*carriage)->tmp_pos = (*carriage)->pos + 1;
			else
				(*carriage)->tmp_pos = 0;
			i = 0;
			while (i < ARGS)
				arg_found[i++] = core[((*carriage)->tmp_pos)];
			//third = core[((*carriage)->tmp_pos)];
			//first = core[((*carriage)->tmp_pos)];
			//second = core[((*carriage)->tmp_pos)];
			//forth = core[((*carriage)->tmp_pos)];
			arg_found[ARG3] = arg_found[ARG3] >> 6; 
			arg_found[ARG2] = arg_found[ARG2] << 4;
			arg_found[ARG2] = arg_found[ARG2] >> 6;
			arg_found[ARG1] = arg_found[ARG1] >> 6;
			ft_printf("ARG TYPES %i  %i  %i\n", arg_found[ARG1],arg_found[ARG2],arg_found[ARG3]);
			(*carriage)->arg_types[ARG1] = arg_found[ARG1];
			(*carriage)->arg_types[ARG2] = arg_found[ARG2];
			(*carriage)->arg_types[ARG3] = arg_found[ARG3];
			(*carriage)->args_found[ARG1] = first_arg((u_int32_t)arg_found[ARG1], *carriage, info, core);
			(*carriage)->args_found[ARG2] = second_arg((u_int32_t)arg_found[ARG2], *carriage, info, core);
			(*carriage)->args_found[ARG3] = third_arg((u_int32_t)arg_found[ARG3], *carriage, info, core);
			//ft_printf("wait %i %lli\n", third_arg((u_int32_t)arg_found[ARG3], *carriage, info, core), (*carriage)->args_found[ARG3]);
			ft_printf("first = %i second %i  third %i\n", (*carriage)->args_found[ARG1], (*carriage)->args_found[ARG2], (*carriage)->args_found[ARG3]);
			op_table[(*carriage)->statement_code - 1](core, carriage, info);
			//move carriage
			exit (0);
			//ft_printf("1st %i  2nd %i  3rd %i    4th %i\n", first, second, third, forth);
			//exit (0);
				//T_DIR = 2
				//T_IND = 3
				//T_REG = 1
				//forth should always be 00
				//function to check arguments are valid in relation to statecode
				//and collect the values, making sure they are valid
				//collect_arg(1, &core[(*carriage)->pos], *carriage, 0);
			//	++tmp_pos;
			//}
		}
		else
		{}
	}
	else
	{
		if ((*carriage)->pos  == MEM_SIZE - 1)
		{
			(*carriage)->pos = 0;
			(*carriage)->current  = &core[0];
		}
		else
		{
			(*carriage)->pos++;
			(*carriage)->current++;
		}
	}
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