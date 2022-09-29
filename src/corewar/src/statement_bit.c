
#include "vm.h"

static int	check_arg_type_first(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[0] == R)
		return ((*carriage)->registry[arg[0] - 1]);
	else if ((*carriage)->arg_types[0] == I)
	{
		// call read function that will return correct int
		// arg[0] = read_function()
		//return (read__function());
		if (core || info)
			ft_printf("have core and info\n");
	}
	return (arg[0]);
}

static int	check_arg_type_second(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[1] == R)
		return ((*carriage)->registry[arg[1] - 1]);
	else if ((*carriage)->arg_types[1] == I)
	{
		// call read function that will return correct int
		// arg[0] = read_function()
		//return (read__function());
		if (core || info)
			ft_printf("have core and info\n");
	}
	return (arg[1]);
}

//core is needed in the read function - i know they are identical
void	xor(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	arg[0] = check_arg_type_first(arg, core, carriage, info);
	arg[1] = check_arg_type_second(arg, core, carriage, info);
	sum = arg[0] ^ arg[1];
	(*carriage)->registry[arg[2] - 1] = sum;
	update_carry(sum, carriage);
}

//core is needed in the read function - i know they are identical
void	or(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	arg[0] = check_arg_type_first(arg, core, carriage, info);
	arg[1] = check_arg_type_second(arg, core, carriage, info);
	sum = arg[0] | arg[1];
	(*carriage)->registry[arg[2] - 1] = sum;
	update_carry(sum, carriage);
}

//core is needed in the read function
void	and(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	arg[0] = check_arg_type_first(arg, core, carriage, info);
	arg[1] = check_arg_type_second(arg, core, carriage, info);
	sum = arg[0] & arg[1];
	(*carriage)->registry[arg[2] - 1] = sum;
	update_carry(sum, carriage);
}
