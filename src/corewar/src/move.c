/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:01:56 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/11 16:05:19 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	make_move_tmp(t_carriage **carriage, int move)
{
	if ((*carriage)->tmp_pos + move >= MEM_SIZE)
	{
		(*carriage)->tmp_pos = ((*carriage)->tmp_pos + move) % MEM_SIZE;
	}
	else
		(*carriage)->tmp_pos += move;
}

void	make_move(t_carriage **carriage, int move, int *total)
{
	if ((*carriage)->pos + move >= MEM_SIZE)
		(*carriage)->pos = ((*carriage)->pos + move) % MEM_SIZE;
	else
		(*carriage)->pos += move;
	*total += move;
	//ft_printf("total: %d	", *total);
}

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
		//ft_printf("argt: %d argf: %d	", (*carriage)->arg_types[i], (*carriage)->args_found[i]);
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
