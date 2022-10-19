/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:01:56 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/18 15:35:17 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Moving the tmp_pos (which is used to collect args with
	changes carriage position, incase of error)	*/
void	make_move_tmp(t_carriage **carriage, int move)
{
	if ((*carriage)->tmp_pos + move >= MEM_SIZE)
	{
		(*carriage)->tmp_pos = ((*carriage)->tmp_pos + move) % MEM_SIZE;
	}
	else
		(*carriage)->tmp_pos += move;
}

/*	Moving position, taking into account cyclical nature of
	the core memory	*/
void	make_move(t_carriage **carriage, int move, int *total)
{
	if ((*carriage)->pos + move >= MEM_SIZE)
		(*carriage)->pos = ((*carriage)->pos + move) % MEM_SIZE;
	else
		(*carriage)->pos += move;
	*total += move;
}

/*	moving carriages after statement code execution 
	according to args types	*/
void	move_carriage(t_carriage **carriage, int *total)
{
	int	i;

	i = 0;
	if (g_operations[PCB][(*carriage)->statement_code - 1] == TRUE)
		make_move(carriage, 2, total);
	else
		make_move(carriage, 1, total);
	while (i < 3)
	{
		if ((*carriage)->arg_types[i] == 1)
			make_move(carriage, 1, total);
		else if ((*carriage)->arg_types[i] == 3)
			make_move(carriage, 2, total);
		else if ((*carriage)->arg_types[i] == 2)
			make_move(carriage, g_operations[SIZE] \
			[(*carriage)->statement_code - 1], total);
		++i;
	}
}
