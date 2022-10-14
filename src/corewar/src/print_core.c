/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:56:42 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:56:44 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_color(t_info *info, int i)
{
	t_carriage	*carriage;

	if (info->flag[DC_FLAG] >= 0 || info->flag[DI_FLAG] >= 0 || \
		info->flag[C_FLAG] >= 0)
	{
		carriage = info->head_carriage;
		while (carriage)
		{
			if (carriage->pos == i)
				ft_printf(GREEN);
			carriage = carriage->next;
		}
	}
}

static void	print_newline_or_space(int *line, int i)
{
	if (*line >= 64)
	{
		ft_printf("\n");
		*line = 0;
		if (i >= MEM_SIZE)
			return ;
		ft_printf("%#0.4x : ", i);
	}
	else
		ft_printf(" ");
}

void	print_core(uint8_t core[MEM_SIZE], t_info *info)
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		print_color(info, i);
		if (core[i] < 16)
			ft_printf("0%x", core[i]);
		else
			ft_printf("%x", core[i]);
		if (info->flag[DC_FLAG] >= 0 || info->flag[DI_FLAG] >= 0 || \
			info->flag[C_FLAG] >= 0)
			ft_printf(RESET);
		++line;
		++i;
		print_newline_or_space(&line, i);
	}
}
