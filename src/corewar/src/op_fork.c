/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:25 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:57:26 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_arg(t_carriage **carriage)
{
	int	i;

	i = 0;
	while (i < ARGS)
	{
		(*carriage)->arg_types[i] = 0;
		(*carriage)->args_found[i++] = 0;
	}
}

static int	copy_carriage(t_info **info, t_carriage *carriage, int new_pos)
{
	t_carriage	*new;
	int			i;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (ERROR);
	(*info)->carriage_count++;
	new->id = (*info)->carriage_count;
	new->carry = carriage->carry;
	new->last_live_call = carriage->last_live_call;
	new->delay = 0;
	new->pos = new_pos;
	new->statement_code = OP_NULL;
	i = -1;
	while (++i < REG_NUMBER)
		new->registry[i] = carriage->registry[i];
	set_arg(&new);
	new->next = (*info)->head_carriage;
	(*info)->head_carriage = new;
	return (0);
}

void	op_fork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			pos;
	int16_t		sum;
	static int	found = FALSE;

	if (print_command(info) == TRUE && core)
		v_flag4_one_arg(carriage, "fork");
	sum = (int16_t)(*carriage)->args_found[ARG1];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if (print_command(info) == TRUE)
		ft_printf("(%d)\n", pos);
	limit_jump(&pos);
	copy_carriage(&info, *carriage, pos);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

void	op_lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			pos;
	static int	found = FALSE;

	if (print_command(info) == TRUE && core)
		v_flag4_one_arg(carriage, "lfork");
	pos = (*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1];
	if (print_command(info) == TRUE)
		ft_printf("(%d)\n", pos);
	limit_jump(&pos);
	copy_carriage(&info, *carriage, pos);
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}
