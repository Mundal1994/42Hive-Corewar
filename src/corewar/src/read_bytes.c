/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:51:38 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/19 10:56:05 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

static void	choice_type(int third, int size, int *j, int *type)
{
	if (third == 2 || third == 0)
	{
		*type = size;
		*j = (size * 2) - 1;
	}
	else
	{
		*type = 2;
		*j = 3;
	}
}

int	read_bytes(u_int32_t third, int	pos, uint8_t core[MEM_SIZE], int size)
{
	int	i;
	int	hold;
	int	j;
	int	type;

	i = 0;
	limit_jump(&pos);
	choice_type(third, size, &j, &type);
	third = 0;
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
	return (third);
}
