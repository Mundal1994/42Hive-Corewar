/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:10:26 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/11 16:12:51 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	read_bytes(u_int32_t third, int	pos, uint8_t core[MEM_SIZE], int size)
{
	int	i;
	int	hold;
	int	j;
	int	type;

	i = 0;
	limit_jump(&pos);
	if (third == 2 || third == 0)
	{
		type = size;
		j = (size * 2) - 1;
	}
	else
	{
		type = 2;
		j = 3;
	}
	third = 0;
	//ft_printf("pos: %d size: %d\n", pos, size);
	while (i < type)
	{
		if ((pos + i) >= MEM_SIZE)
			pos = ((pos + i) % MEM_SIZE) - i;
		hold = core[pos + i];
		third += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		third += (hold % 16) * ft_pow(16, j--);
		++i;
	}
	//ft_printf("VALUE %d\n", third);
	return (third);
}

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
		if ((*carriage)->arg_types[first] == 2)
			i = g_operations[SIZE][(*carriage)->statement_code - 1];
		else
			i = 2;
		first = read_bytes((*carriage)->arg_types[first], (*carriage)->tmp_pos, \
		core, g_operations[SIZE][(*carriage)->statement_code - 1]);
		make_move_tmp(carriage, i);
		return (first);
	}
	return (-1);
}
