/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:51:38 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/19 11:16:59 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Choice function collecting bytes from the core depending on the type of
	argument being read	*/
static void	choice_type(int choice, int size, int *j, int *type)
{
	if (choice == 2 || choice == 0)
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

/*	reads bytes from the core and returns the number */
int	read_bytes(u_int32_t choice, int pos, uint8_t core[MEM_SIZE], int size)
{
	int	i;
	int	hold;
	int	j;
	int	type;

	i = 0;
	limit_jump(&pos);
	choice_type(choice, size, &j, &type);
	choice = 0;
	while (i < type)
	{
		if ((pos + i) >= MEM_SIZE)
			pos = ((pos + i) % MEM_SIZE) - i;
		hold = core[pos + i];
		choice += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		choice += (hold % 16) * ft_pow(16, j--);
		++i;
	}
	return (choice);
}
