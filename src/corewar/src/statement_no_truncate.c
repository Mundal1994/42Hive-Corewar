
#include "vm.h"

//pretty much a copy of ld but with no % IDX_MOD
void	lld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[ARG1] == I)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos - ((int16_t)(*carriage)->args_found[ARG1] * -1), core, 2);//orig machine read 2 instead of four
		else
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1], core, 2);
	}
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_two_arg(carriage, "lld", ARG2);
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->args_found[ARG1];
	//still update carry?
	//update_carry((*carriage)->args_found[0], carriage);
}

void	aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	// if (info->flag[V_FLAG] == 4)
	// 	v_flag4_one_arg(carriage, "aff");//aff doesn't show up in flag -v 4??
	if (info->flag[A_FLAG] && core && info)
		ft_printf("%c\n", (char)(*carriage)->args_found[ARG1]);
}
