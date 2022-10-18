/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:40 by molesen           #+#    #+#             */
/*   Updated: 2022/10/18 12:22:23 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
updates the carriages carry depending on the number put in as a variable
*/
void	update_carry(int nbr, t_carriage **carriage)
{
	if (!nbr)
		(*carriage)->carry = TRUE;
	else
		(*carriage)->carry = FALSE;
}

/*	puts nbr in the core	*/
void	put_nbr(uint8_t core[MEM_SIZE], int pos, uint32_t nbr)
{
	uint32_t	value;
	uint32_t	result;
	int			j;

	value = nbr;
	j = 3;
	while (j >= 0)
	{
		//ft_printf("result %i\n", (value % 16) * ft_pow(16, 0));
		result = (value % 16) * ft_pow(16, 0);
		value /= 16;
		//ft_printf("result %i\n", (value % 16) * ft_pow(16, 1));
		result += (value % 16) * ft_pow(16, 1);
		value /= 16;
		if (pos + j >= MEM_SIZE)
			core[(pos + j) - MEM_SIZE] = result;
		else
			core[pos + j] = result;
		j--;
	}
}

/*	makes sure the carriages stay within the limit of the core/arena	*/
void	limit_jump(int *pos)
{
	if (*pos >= MEM_SIZE)
		*pos %= MEM_SIZE;
	else if (*pos < 0)
		*pos = MEM_SIZE - (*pos * -1);
}

/*	updates arg values based on their types	*/
void	update_arg_values(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	int64_t *arg, int count)
{
	if ((*carriage)->arg_types[count] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[count] == I)
	{
		if (*arg < 0)
			*arg = (int32_t)read_bytes(0, (*carriage)->pos - ((*arg * -1) \
			% IDX_MOD), core, SIZE);
		else
			*arg = (int32_t)read_bytes(0, (*carriage)->pos + (*arg % IDX_MOD), \
			core, SIZE);
	}
	else
		*arg = (int16_t)(*arg);
}
