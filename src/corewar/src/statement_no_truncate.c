
#include "vm.h"

//pretty much a copy of ld but with no % IDX_MOD
void	lld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[0] == I)
	{
		(*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos + (*carriage)->args_found[0], core, info->operations[SIZE][(*carriage)->statement_code - 1]);
		if (core || info)
			ft_printf("is arg type I\n");
	}
	(*carriage)->registry[(*carriage)->args_found[1] - 1] = (*carriage)->args_found[0];
	
	//still update carry?
	//update_carry((*carriage)->args_found[0], carriage);
}

void	aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if (info->flag[A_FLAG] && core && info)
		ft_printf("%c\n", (char)(*carriage)->args_found[0]);
	else
		ft_printf("AFF FLAG NOT ON\n");
}