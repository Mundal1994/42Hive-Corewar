/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:05:13 by molesen           #+#    #+#             */
/*   Updated: 2022/10/18 12:21:45 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	print flag -v 2 (cycle count and cycle to die value)	*/
static void	print_cycle_text(t_info *info, int die)
{
	if (die == TRUE)
		ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
	else
		ft_printf("It is now cycle %d\n", info->total_cycles);
}

/*	prints the different variations of the dump flag	*/
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
