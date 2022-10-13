
#include "vm.h"

void	ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;
	if ((*carriage)->arg_types[ARG1] == I && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] * -1) % IDX_MOD), core, SIZE);
		else
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] % IDX_MOD), core, SIZE);
	}
	if (print_command(info) == TRUE)
		v_flag4_two_arg(carriage, "ld", ARG2);
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->args_found[ARG1];
	update_carry((*carriage)->args_found[ARG1], carriage);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

//pretty much a copy of ld but with no % IDX_MOD
void	lld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;
	if ((*carriage)->arg_types[ARG1] == I)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos - ((int16_t)(*carriage)->args_found[ARG1] * -1), core, 2);//orig machine read 2 instead of four
		else
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1], core, 2);
	}
	if (print_command(info) == TRUE && info)
		v_flag4_two_arg(carriage, "lld", ARG2);
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->args_found[ARG1];
	//still update carry?
	update_carry((*carriage)->args_found[ARG1], carriage);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

void	st(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;
	static int	found = FALSE;

	if (print_command(info) == TRUE && info)
		v_flag4_two_arg(carriage, "st", ARG1);
	if ((*carriage)->arg_types[ARG2] == R)
		(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1];
	else if ((*carriage)->arg_types[ARG2] == I)
	{
		//ft_printf("%d\n: ", (int16_t)(*carriage)->args_found[ARG2]);
		if ((int16_t)(*carriage)->args_found[ARG2] < 0)
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG2] * -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG2] % IDX_MOD);
		limit_jump(&pos);
		put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	}
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}
