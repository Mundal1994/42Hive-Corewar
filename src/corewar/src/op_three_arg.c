/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_three_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:14 by molesen           #+#    #+#             */
/*   Updated: 2022/10/19 11:25:25 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
takes the sum of the values you get from the registries that was passed
as first and second argument. the sum is written inside the registry passed
as the third argument. If sum was equal to zero the 'carry' will be 1
otherwise it will be 0
*/
void	op_add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			sum;
	static int	found = FALSE;

	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && core && info)
		v_flag4_three_arg(carriage, "add", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] + \
		(*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)sum;
	update_carry(sum, carriage);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*	same behaviour as op_add except it minuses the two registry numbers	*/
void	op_sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			sum;
	static int	found = FALSE;

	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && core && info)
		v_flag4_three_arg(carriage, "sub", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] - \
		(*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)sum;
	update_carry(sum, carriage);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
writes the value of the registry passed as the first argument into the core.
the location where it will be written can be found by the carriages current
position + second argument + third argument % IDX_MOD
*/
void	op_sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			pos;
	int			sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG3], ARG3);
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && info)
		v_flag4_three_arg(carriage, "sti", ARG1);
	sum = (*carriage)->args_found[ARG2] + \
		(*carriage)->args_found[ARG3];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", \
		(*carriage)->args_found[ARG2], \
		(*carriage)->args_found[ARG3], sum, pos);
	limit_jump(&pos);
	put_nbr(core, pos, \
		(uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
reads a number from the core and places it in the registry passed as the third
argument. The number can be found by the carriages current position + first
argument + second argument % IDX_MOD
*/
void	op_ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			value;
	int			pos;
	int			sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && info)
		v_flag4_three_arg(carriage, "ldi", ARG3);
	sum = (*carriage)->args_found[ARG1] + \
		(*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", \
		(*carriage)->args_found[ARG1], \
		(*carriage)->args_found[ARG2], sum, pos);
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)value;
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
resembles the op_ldi command.
writes value to the registry that was passed as the third parameter. The number
that will be placed there can be found by adding the carriage current position
+ first argument + second argument. In this one we will not truncate by IDX_MOD
*/
void	op_lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			value;
	int			pos;
	int			sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0 && info)
		v_flag4_three_arg(carriage, "lldi", ARG3);
	sum = (*carriage)->args_found[ARG1] + (*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1);
	else
		pos = (*carriage)->pos + sum;
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0)
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", \
		(*carriage)->args_found[ARG1], (*carriage)->args_found[ARG2], sum, pos);
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = (int32_t)value;
	update_carry(value, carriage);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}
