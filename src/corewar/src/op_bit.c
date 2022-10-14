/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:31 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:57:33 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

void	op_xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (print_command(info) == TRUE && info)
		v_flag4_three_arg(carriage, "xor", ARG3);
	sum = (*carriage)->args_found[ARG1] ^ (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

void	op_or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (print_command(info) == TRUE && info)
		v_flag4_three_arg(carriage, "or", ARG3);
	sum = (*carriage)->args_found[ARG1] | (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

void	op_and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (print_command(info) == TRUE && info)
		v_flag4_three_arg(carriage, "and", ARG3);
	sum = (*carriage)->args_found[ARG1] & (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}
