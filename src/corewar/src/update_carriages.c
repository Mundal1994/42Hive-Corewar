/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/09/29 11:25:56 by jdavis           ###   ########.fr       */
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

void perform_statement_code(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	u_int8_t	compare;
	int			first;
	int			second;
	int			third;
	int			forth;
	int			tmp_pos;

	if (core[(*carriage)->pos] >= 1 && core[(*carriage)->pos] <= 16)
	{
		//not sure if can just compare value of typecode element
		//is arguments arent valid or registry isnt valid, skip all of those bytes
		if (info->operations[PCB][core[(*carriage)->pos]] == 1) //statements using typecode
		{
			if ((*carriage)->pos + 1 <= MEM_SIZE - 1)
				tmp_pos = (*carriage)->pos + 1;
			else
				tmp_pos = 0;
			compare = core[(tmp_pos)];
			while (tmp_pos <= MEM_SIZE - 1)
			{
				third = compare << 6; 
				second = (compare >> 4) << 6;
				first = (compare >> 6) << 6;
				forth = compare << 6;
				//T_DIR = 128
				//T_IND = 192
				//T_REG = 64
				//forth should always be 00
				//function to check arguments are valid in relation to statecode
				//and collect the values, making sure they are valid
				//collect_arg(1, &core[(*carriage)->pos], *carriage, 0);
				++tmp_pos;
			}
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

int	update_carriages(uint8_t core[MEM_SIZE], t_info *info)
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
			perform_statement_code(core, &carriage, info);
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




*/