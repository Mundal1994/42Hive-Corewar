
#include "vm.h"

int	print_command(t_info *info)
{
	if (info->flag[V_FLAG] >= 4 && info->flag[V_FLAG] <= 6)
		return (TRUE);
	if (info->flag[V_FLAG] >= 12 && info->flag[V_FLAG] <= 14)
		return (TRUE);
	if (info->flag[V_FLAG] >= 20 && info->flag[V_FLAG] <= 24)
		return (TRUE);
	return (FALSE);
}

void	zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
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
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;
	if (print_command(info) == TRUE)
		v_flag4_one_arg(carriage, "live");
	(*carriage)->last_live_call = info->total_cycles;//removed +1
	info->live_statement += 1;
	if ((*carriage)->args_found[ARG1] >= (info->champ_total * -1) && core && info && \
		(*carriage)->args_found[ARG1] <= -1)
	{
		info->winner = (*carriage)->args_found[ARG1] * -1;
		if (info->flag[V_FLAG] == 1 || info->flag[V_FLAG] == 3 || info->flag[V_FLAG] == 5 || \
			info->flag[V_FLAG] == 9 || info->flag[V_FLAG] == 11 || \
			(info->flag[V_FLAG] >= 13 && info->flag[V_FLAG] <= 17) || info->flag[V_FLAG] == 19 || \
			(info->flag[V_FLAG] >= 21 && info->flag[V_FLAG] <= 24))
			ft_printf("Player %d (%s) is said to be alive\n", info->winner, info->champ_names[info->winner - 1]);// decide if we want to print name of the player as well
		//ft_printf("winner updated: %d\n", info->winner);
	}
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

void	aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;
	// if (print_command(info) == TRUE)
	// 	v_flag4_one_arg(carriage, "aff");//aff doesn't show up in flag -v 4??
	if (info->flag[A_FLAG] && core && info)
		ft_printf("%c\n", (char)(*carriage)->args_found[ARG1]);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}
