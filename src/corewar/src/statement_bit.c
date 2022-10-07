
#include "vm.h"

static void	read_bytes_int16(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	int16_t temp;

	temp = (int16_t)(*arg);
	// ft_printf("CHECK\n");
	// if ((*carriage)->id == 8 && (*carriage)->statement_code == 6)
	// 	ft_printf("BEFORE arg being read %d    %d\n", (*carriage)->pos - (temp * -1) % IDX_MOD, (*carriage)->pos + temp % IDX_MOD);
	if (temp < 0)
		*arg = read_bytes(0, (*carriage)->pos - (temp * -1) % IDX_MOD, core, SIZE);
	else
		*arg = read_bytes(0, (*carriage)->pos + temp % IDX_MOD, core, SIZE);
}

void	check_first_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	if ((*carriage)->arg_types[0] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[0] == I)
	{
		read_bytes_int16(core, carriage, arg);
		// if (*arg < 0)
		// 	*arg = read_bytes(0, (*carriage)->pos - (*arg * -1) % IDX_MOD, core, SIZE);
		// else
		// 	*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
	}
}

void	check_second_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	if ((*carriage)->arg_types[1] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[1] == I)
	{
		read_bytes_int16(core, carriage, arg);
		// if (*arg < 0)
		// 	*arg = read_bytes(0, (*carriage)->pos - (*arg * -1) % IDX_MOD, core, SIZE);
		// else
		// 	*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
	}
}

void	check_third_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	if ((*carriage)->arg_types[2] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[2] == I)
	{
		read_bytes_int16(core, carriage, arg);
		// if (*arg < 0)
		// 	*arg = read_bytes(0, (*carriage)->pos - (*arg * -1) % IDX_MOD, core, SIZE);
		// else
		// 	*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
	}
}

void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
	if (info->flag[V_FLAG] == 4)
		v_flag4_three_arg(carriage, "xor", ARG3);
	sum = (*carriage)->args_found[0] ^ (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!info)
		ft_printf("hah\n");
}

void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
	if (info->flag[V_FLAG] == 4)
		v_flag4_three_arg(carriage, "or", ARG3);
	sum = (*carriage)->args_found[0] | (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!info)
		ft_printf("hah\n");
}

void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
	if (info->flag[V_FLAG] == 4)
		v_flag4_three_arg(carriage, "and", ARG3);
	// if ((*carriage)->id == 8)
	// {
	// 	ft_printf("\nCARRIAGE NBR: %d\n", (*carriage)->id);
	// 	ft_printf(" statement code   %i    pos %i\n", core[(*carriage)->pos], (*carriage)->pos);
	// 	ft_printf("typecode %i   pcb %i   pos %d\n", core[(*carriage)->pos + 1], info->operations[PCB][(*carriage)->statement_code - 1], (*carriage)->pos);
	// 	ft_printf("arg0: %d	arg1: %d	arg2: %d\n", (*carriage)->args_found[0], (*carriage)->args_found[1], (*carriage)->args_found[2]);
	// }
	sum = (*carriage)->args_found[0] & (*carriage)->args_found[1];
	if ((*carriage)->id == 8)
	sum = -1;
	if ((*carriage)->id == 8)
		ft_printf("SUM: %d\n", sum);
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!info)
		ft_printf("hah\n");
}
