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

	carriage = info->head;
	while (carriage)
	{
		if (carriage->delay == 0)//means it moved last cycle or just been initiated
		{
			//set_statement_code(&carriage);
		}
		if (carriage->delay > 0)
			carriage->delay -= 1;
		if (carriage->delay == 0)
		{
			//perform_statement_code() and move carriage
			// if cannot perform statement code move to next byte.
		}
		carriage = carriage->next;
	}
	return (0);
}
