
#include "vm.h"

// dont know if this one works

void	check_arg_type(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info, int64_t *arg)
{
	if ((*carriage)->arg_types[0] == R)
		*arg = (*carriage)->registry[(*carriage)->args_found[0] - 1];
	else if ((*carriage)->arg_types[0] == I)
	{
		*arg = read_bytes(0, (*carriage)->pos + *arg % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
		// call read function that will return correct int
		// (*carriage)->args_found[0] = read_function()
		//return (read__function());
		if (core || info)
			ft_printf("have core and info\n");
	}
	// else

	// return ((*carriage)->args_found[0]);
}

// static int	check_arg_type_second(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
// {
// 	if ((*carriage)->arg_types[1] == R)
// 		return ((*carriage)->registry[(*carriage)->args_found[1] - 1]);
// 	else if ((*carriage)->arg_types[1] == I)
// 	{
// 		//return ((*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]));
// 		// call read function that will return correct int
// 		// (*carriage)->args_found[0] = read_function()
// 		//return (read__function());
// 		if (core || info)
// 			ft_printf("have core and info\n");
// 	}
// 	return ((*carriage)->args_found[1]);
// }

//core is needed in the read function - i know they are identical
void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	//(*carriage)->args_found[1] = check_arg_type_second(core, carriage, info);
	sum = (*carriage)->args_found[0] ^ (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}

//core is needed in the read function - i know they are identical
void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	//(*carriage)->args_found[1] = check_arg_type_second(core, carriage, info);
	sum = (*carriage)->args_found[0] | (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}

//core is needed in the read function
void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	check_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	//(*carriage)->args_found[1] = check_arg_type_second(core, carriage, info);
	sum = (*carriage)->args_found[0] & (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}
