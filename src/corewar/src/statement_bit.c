
#include "vm.h"

void	check_first_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	if ((*carriage)->arg_types[0] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[0] == I)
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
}

void	check_second_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	if ((*carriage)->arg_types[1] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[1] == I)
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
}

void	check_third_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg)
{
	if ((*carriage)->arg_types[2] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[2] == I)
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, SIZE);
}

void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
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
	//ft_printf("arg0: %d	arg1: %d	arg2: %d\n", (*carriage)->args_found[0], (*carriage)->args_found[1], (*carriage)->args_found[2]);
	sum = (*carriage)->args_found[0] & (*carriage)->args_found[1];
	//ft_printf("SUM: %d\n", sum);
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!info)
		ft_printf("hah\n");
}
