
#include "vm.h"

void	check_first_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, int64_t *arg)
{
	if ((*carriage)->arg_types[0] == R)
		*arg = (*carriage)->registry[(*carriage)->args_found[0] - 1];
	else if ((*carriage)->arg_types[0] == I)
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
}

void	check_second_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, int64_t *arg)
{
	if ((*carriage)->arg_types[1] == R)
		*arg = (*carriage)->registry[(*carriage)->args_found[0] - 1];
	else if ((*carriage)->arg_types[1] == I)
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
}

void	check_third_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, int64_t *arg)
{
	if ((*carriage)->arg_types[2] == R)
		*arg = (*carriage)->registry[(*carriage)->args_found[0] - 1];
	else if ((*carriage)->arg_types[2] == I)
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
}

void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	sum = (*carriage)->args_found[0] ^ (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}

void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	sum = (*carriage)->args_found[0] | (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}

void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_first_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	sum = (*carriage)->args_found[0] & (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}
