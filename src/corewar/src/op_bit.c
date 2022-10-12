
#include "vm.h"

void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "xor", ARG3);
	sum = (*carriage)->args_found[ARG1] ^ (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "or", ARG3);
	sum = (*carriage)->args_found[ARG1] | (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "and", ARG3);
	sum = (*carriage)->args_found[ARG1] & (*carriage)->args_found[ARG2];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}
