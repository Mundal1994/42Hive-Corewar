/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:10:26 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/19 11:06:55 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Boolen function to detemine if first complies with the rules for 
	the particular statement code for args 2 and three	*/
static int	if_arg_two_three(u_int32_t first, t_carriage **carriage)
{
	if (((*carriage)->arg_types[first] == 2 && \
		(g_operations[first][(*carriage)->statement_code - 1] == 2 || \
		g_operations[first][(*carriage)->statement_code - 1] == 4 || \
		g_operations[first][(*carriage)->statement_code - 1] == 6 || \
		g_operations[first][(*carriage)->statement_code - 1] == 7)) || \
		((*carriage)->arg_types[first] == 3 && \
		(g_operations[first][(*carriage)->statement_code - 1] == 3 || \
		g_operations[first][(*carriage)->statement_code - 1] == 5 || \
		g_operations[first][(*carriage)->statement_code - 1] == 6 || \
		g_operations[first][(*carriage)->statement_code - 1] == 7)))
		return (TRUE);
	return (FALSE);
}

/*	Boolen function to detemine if first complies with the rules for 
	the particular statement code for arg 1	*/
static int	if_arg_one(u_int32_t first, t_carriage **carriage)
{
	if ((*carriage)->arg_types[first] == 1 && \
	(g_operations[first][(*carriage)->statement_code - 1] == 1 \
	|| g_operations[first][(*carriage)->statement_code - 1] == 4 \
	|| g_operations[first][(*carriage)->statement_code - 1] == 5 \
	|| g_operations[first][(*carriage)->statement_code - 1] == 7))
		return (TRUE);
	return (FALSE);
}

/*	Choice function to determine how to move the carriage postions
	after execution	*/
static int	choice_i(int choice, t_carriage **carriage)
{
	if (choice == 2)
		return (g_operations[SIZE][(*carriage)->statement_code - 1]);
	else
		return (2);
}

/*	reading the bytes off of the board depending on the argument	*/
int64_t	read_args(u_int32_t first, t_carriage **carriage, \
u_int8_t core[MEM_SIZE])
{
	int	i;
	int	temp;

	if (g_operations[first][(*carriage)->statement_code - 1] == 0)
	{
		(*carriage)->arg_types[first] = 0;
		return (0);
	}
	if (if_arg_one(first, carriage) == TRUE)
	{
		if (core[(*carriage)->tmp_pos] < 1 || core[(*carriage)->tmp_pos] > 16)
			return (-1);
		temp = core[(*carriage)->tmp_pos];
		make_move_tmp(carriage, 1);
		return (temp);
	}
	else if (if_arg_two_three(first, carriage) == TRUE)
	{
		i = choice_i((*carriage)->arg_types[first], carriage);
		first = read_bytes((*carriage)->arg_types[first], (*carriage)->tmp_pos, \
		core, g_operations[SIZE][(*carriage)->statement_code - 1]);
		make_move_tmp(carriage, i);
		return (first);
	}
	return (-1);
}
