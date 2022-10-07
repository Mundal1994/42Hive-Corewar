
#include "vm.h"

void	update_arg_values(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg, int count)
{
	if ((*carriage)->arg_types[count] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[count] == I)
	{
		if (*arg < 0)
			*arg = read_bytes(0, (*carriage)->pos - (*arg * -1) % IDX_MOD, core, SIZE);
		else
			*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
	}
}

void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "xor", ARG3);
	sum = (*carriage)->args_found[ARG1] ^ (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
}

void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "or", ARG3);
	sum = (*carriage)->args_found[ARG1] | (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
}

void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "and", ARG3);
	sum = (*carriage)->args_found[ARG1] & (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
}
