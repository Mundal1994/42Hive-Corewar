/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:22:55 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/19 11:19:40 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_flag16(uint8_t core[MEM_SIZE], t_carriage **carriage, \
	int total, int prev)
{
	int	i;

	ft_printf("ADV %d ", total);
	if (prev == 0)
		ft_printf("(0x0000 -> %#0.4x) ", (*carriage)->pos);
	else if (prev > (*carriage)->pos)
		ft_printf("(%#0.4x -> %#0.4x) ", prev, (*carriage)->pos + MEM_SIZE);
	else if ((*carriage)->pos == 0)
		ft_printf("(%#0.4x -> 0x0000) ", prev);
	else
		ft_printf("(%#0.4x -> %#0.4x) ", prev, (*carriage)->pos);
	i = 0;
	while (i < total)
	{
		if (prev + i >= MEM_SIZE)
			prev = 0 - i;
		if (core[prev + i] < 16)
			ft_printf("0%x ", core[prev + i]);
		else
			ft_printf("%x ", core[prev + i]);
		++i;
	}
	ft_putchar('\n');
}
