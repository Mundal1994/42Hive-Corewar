
#include "vm.h"

static int	check_arg_type_first(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[0] == R)
		return ((*carriage)->registry[(*carriage)->args_found[0] - 1]);
	else if ((*carriage)->arg_types[0] == I)
	{
		// call read function that will return correct int
		// (*carriage)->args_found[0] = read_function()
		//return (read__function());
		if (core || info)
			ft_printf("have core and info\n");
	}
	return ((*carriage)->args_found[0]);
}

static int	check_arg_type_second(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[1] == R)
		return ((*carriage)->registry[(*carriage)->args_found[1] - 1]);
	else if ((*carriage)->arg_types[1] == I)
	{
		// call read function that will return correct int
		// (*carriage)->args_found[0] = read_function()
		//return (read__function());
		if (core || info)
			ft_printf("have core and info\n");
	}
	return ((*carriage)->args_found[1]);
}

//core is needed in the read function - i know they are identical
void	xor(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	(*carriage)->args_found[0] = check_arg_type_first(core, carriage, info);
	(*carriage)->args_found[1] = check_arg_type_second(core, carriage, info);
	sum = (*carriage)->args_found[0] ^ (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}

//core is needed in the read function - i know they are identical
void	or(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	(*carriage)->args_found[0] = check_arg_type_first(core, carriage, info);
	(*carriage)->args_found[1] = check_arg_type_second(core, carriage, info);
	sum = (*carriage)->args_found[0] | (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}

//core is needed in the read function
void	and(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	(*carriage)->args_found[0] = check_arg_type_first(core, carriage, info);
	(*carriage)->args_found[1] = check_arg_type_second(core, carriage, info);
	sum = (*carriage)->args_found[0] & (*carriage)->args_found[1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
}
