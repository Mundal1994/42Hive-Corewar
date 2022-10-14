/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:05:13 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 12:07:01 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_cycle_count(t_info *info)
{
	if (info->flag[V_FLAG] == 2 || info->flag[V_FLAG] == 3 || \
		info->flag[V_FLAG] == 6)
		ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
	if (info->flag[V_FLAG] == 7 || info->flag[V_FLAG] == 11 || \
		info->flag[V_FLAG] == 14)
		ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
	if (info->flag[V_FLAG] == 10 || (info->flag[V_FLAG] >= 18 && \
		info->flag[V_FLAG] <= 19))
		ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
	if (info->flag[V_FLAG] == 15 || (info->flag[V_FLAG] >= 22 && \
		info->flag[V_FLAG] <= 23))
		ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
}

int	print_dump_flags(uint8_t core[MEM_SIZE], t_info *info)
{
	print_core(core, info);
	if (info->flag[DI_FLAG] >= 0)
		print_info(info);
	if (info->flag[C_FLAG] >= 0)
		print_carriages(info);
	free_carriage(info);
	return (-1);
}
