
#include "vm.h"

// pass in int arg[3] in all functions to make them more similar?

void	live(int arg, uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	(*carriage)->last_live_call = info->total_cycles + 1;
	if (arg == (*carriage)->registry[0])
	{
		info->winner = arg * -1;
		ft_printf("winner updated: %d\n", info->winner);
	}
	if (!core)// this function doens't need to have passed in core
		ft_printf("no core found\n");
}