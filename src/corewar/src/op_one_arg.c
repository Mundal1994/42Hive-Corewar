/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_one_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:05 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 11:57:07 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

/*	function that determines if commands should be printed to standard output	*/
int	print_command(t_info *info)
{
	if (info->flag[V_FLAG] >= 4 && info->flag[V_FLAG] <= 7)
		return (TRUE);
	if (info->flag[V_FLAG] >= 12 && info->flag[V_FLAG] <= 15)
		return (TRUE);
	if (info->flag[V_FLAG] >= 20 && info->flag[V_FLAG] <= 23)
		return (TRUE);
	return (FALSE);
}

/*
makes carriage able to jump to different positions on the
board with the limitations of IDX_MOD (-512 to 512)
*/
void	op_zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;
	static int	found = FALSE;

	if ((*carriage)->carry && core && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] * -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] % IDX_MOD);
		limit_jump(&pos);
		(*carriage)->pos = pos;
	}
	if (print_command(info) == TRUE)
		v_flag4_one_arg(carriage, "zjmp");
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
calls a player to be alive if the number read from the first argument is
equal to a player ex. if we read the first argument to be -2
then we will call player 2 to be alive
*/
void	op_live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;

	if (print_command(info) == TRUE)
	{
		//ft_printf("pos: %d	", (*carriage)->pos, (*carriage)->args_found);
		v_flag4_one_arg(carriage, "live");
	}
	(*carriage)->last_live_call = info->total_cycles;//removed +1
	info->live_statement += 1;
	if ((*carriage)->args_found[ARG1] >= (info->champ_total * -1) && core \
		&& info && (*carriage)->args_found[ARG1] <= -1)
	{
		info->winner = (*carriage)->args_found[ARG1] * -1;
		if (info->flag[NO_FLAG] == TRUE)
			ft_printf("A process shows that player %d (%s) is alive\n", \
			info->winner, info->champ_names[info->winner - 1]);
		else if (info->flag[V_FLAG] == 1 || info->flag[V_FLAG] == 3 || \
			info->flag[V_FLAG] == 5 || info->flag[V_FLAG] == 7 || \
			info->flag[V_FLAG] == 9 || info->flag[V_FLAG] == 11 || \
			(info->flag[V_FLAG] >= 13 && info->flag[V_FLAG] <= 15) || \
			info->flag[V_FLAG] == 19 || (info->flag[V_FLAG] >= 23 && \
			info->flag[V_FLAG] <= 23) || info->flag[V_FLAG] == 17 || \
			info->flag[V_FLAG] == 21)
			ft_printf("Player %d (%s) is said to be alive\n", \
			info->winner, info->champ_names[info->winner - 1]);
	}
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
prints the correlating number to standard output in the form of a char
this operand only shows if flag -a is active
*/
void	op_aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int32_t		nbr;
	static int	found = FALSE;
	
	if (info->flag[A_FLAG] == TRUE && core && info)
	{
		nbr = (int32_t)(*carriage)->registry[(int32_t)(*carriage)->args_found[ARG1] - 1];
		ft_printf("Aff: %c\n", (char)nbr % 256);
	}
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}
