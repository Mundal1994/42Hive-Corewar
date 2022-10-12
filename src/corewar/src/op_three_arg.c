
#include "vm.h"

void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	if (info->flag[V_FLAG] == 4 && core && info)
		v_flag4_three_arg(carriage, "add", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] + (*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	if (info->flag[V_FLAG] == 4 && core && info)
		v_flag4_three_arg(carriage, "sub", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] - (*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		value;
	int		pos;
	int16_t sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "ldi", ARG3);
	sum = (int16_t)(*carriage)->args_found[ARG1] + (int16_t)(*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
		if (info->flag[V_FLAG] == 4)
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG1], (int16_t)(*carriage)->args_found[ARG2], sum, pos);
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = value;
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	value;
	int	pos;
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "lldi", ARG3);
	sum = (*carriage)->args_found[ARG1] + (*carriage)->args_found[ARG2];// should these also be int16_t limited like the others? or did i have a reason for leaving it like this
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1);
	else
		pos = (*carriage)->pos + sum;
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", (*carriage)->args_found[ARG1], (*carriage)->args_found[ARG2], sum, pos);
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = value;
	update_carry(value, carriage);//one place it said that this function contrary to lld should update carry
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		pos;
	int16_t	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG3], ARG3);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "sti", ARG1);
	sum = (int16_t)(*carriage)->args_found[ARG2] + (int16_t)(*carriage)->args_found[ARG3];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG2], (int16_t)(*carriage)->args_found[ARG3], sum, pos);
	limit_jump(&pos);
	put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}
