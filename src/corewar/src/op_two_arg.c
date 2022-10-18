/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_two_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:56:59 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:57:01 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
writes value from the registry passed as the first parameter to the core.
Location of the written value can be found by the carriage current position +
second argument + IDX_MOD
*/
void	op_st(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			pos;
	static int	found = FALSE;

	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && info)
		v_flag4_two_arg(carriage, "st", ARG1);
	if ((*carriage)->arg_types[ARG2] == R)
		(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = \
		(*carriage)->registry[(*carriage)->args_found[ARG1] - 1];
	else if ((*carriage)->arg_types[ARG2] == I)
	{
		if ((int16_t)(*carriage)->args_found[ARG2] < 0)
			pos = (*carriage)->pos - \
			(((int16_t)(*carriage)->args_found[ARG2] * -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG2] \
			% IDX_MOD);
		limit_jump(&pos);
		put_nbr(core, pos, \
		(uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	}
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
puts a value from the core into the registry passed as the second argument.
the value can be found by reading the following address
carriage current position + first argument % IDX_MOD
carry will be updated: if zero was written to the registry 'carry' is 1
otherwise 'carry' is 0
*/
void	op_ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;

	if ((*carriage)->arg_types[ARG1] == I && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = (int32_t)read_bytes(0, \
			(*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] * -1) \
			% IDX_MOD), core, SIZE);
		else
			(*carriage)->args_found[ARG1] = (int32_t)read_bytes(0, \
			(*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] \
			% IDX_MOD), core, SIZE);
	}
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0)
		v_flag4_two_arg(carriage, "ld", ARG2);
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = \
	(int32_t)(*carriage)->args_found[ARG1];
	update_carry((*carriage)->args_found[ARG1], carriage);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
behaves like the op_ld statement.
except it doesn't use IDX_MOD when finding the address to read from
*/
//pretty much a copy of ld but with no % IDX_MOD
void	op_lld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;

	if ((*carriage)->arg_types[ARG1] == I)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = (int32_t)read_bytes(0, \
			(*carriage)->pos - ((int16_t)(*carriage)->args_found[ARG1] * -1), \
			core, 2);
		else
			(*carriage)->args_found[ARG1] = (int32_t)read_bytes(0, \
			(*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1], core, 2);
	}
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && info)
		v_flag4_two_arg(carriage, "lld", ARG2);
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = \
	(int32_t)(*carriage)->args_found[ARG1];
	update_carry((*carriage)->args_found[ARG1], carriage);//still update carry?
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}
