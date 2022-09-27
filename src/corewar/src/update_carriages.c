/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:33:24 by molesen           #+#    #+#             */
/*   Updated: 2022/09/23 12:33:26 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// static void	set_statement_code(t_carriage **carriage)
// {
	/*
	logic of how to check if it is a possible operation command? just check if it is less than 16
	if (core[(*carriage)->pos] == VALID OPERAND)
		(*carriage)->delay == specific value
	else
		(*carriage)->delay = 0;
		*/
// }

// static void	perform_statement_code(t_info *info)
// {
// 	perform_statement_code() and move carriage
// }

int	update_carriages(t_info *info)
{
	t_carriage	*carriage;

	carriage = info->head_carriage;
	while (carriage)
	{
		if (carriage->delay == 0)//means it moved last cycle or just been initiated
		{
			//JEFF----------------
			//set_statement_code(&carriage);
		}
		if (carriage->delay > 0)
			carriage->delay -= 1;
		if (carriage->delay == 0)
		{
			//JEFF----------------
			//perform_statement_code() and move carriage
			// if cannot perform statement code move to next byte.
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

*/