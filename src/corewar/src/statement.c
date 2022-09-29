
#include "vm.h"

void	update_carry(int nbr, t_carriage **carriage)
{
	if (!nbr)
		(*carriage)->carry = TRUE;
	else
		(*carriage)->carry = FALSE;
}

void	zjmp(int arg[ARGS], t_carriage **carriage)
{
	int	new;
	int	dif;

	if ((*carriage)->carry)
	{
		new = (*carriage)->pos + arg[0] % IDX_MOD;
		if (new >= MEM_SIZE)// dont know if this is ever the case?? just thinking if number goes over memsize
		{
			dif = new - MEM_SIZE;
			(*carriage)->pos = dif;
		}
		else
			(*carriage)->pos = new;
	}
}

void	live(int arg[ARGS], t_carriage **carriage, t_info *info)
{
	(*carriage)->last_live_call = info->total_cycles + 1;
	if (arg[0] == (*carriage)->registry[0])
	{
		info->winner = arg[0] * -1;
		ft_printf("winner updated: %d\n", info->winner);
	}
}

// now i have registry 1 as 0  and 1 as 2... could also add 17 registry and have the first as a null and never use it??

void	ld(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[1] == I)
	{
		// READ BYTE IN OTHER POSITION OF THE MEM_SIZE to calculate new arg[0]
		//just update arg[0]
		// function that reads four bytes (or 2) from obtained address
		/*
			ex
						pos									core	size (if it is 1 or 2)
			read_bytes((*carriage)->pos + arg[0] % IDX_MOD, core, info->operations[IDX_LD][SIZE]);
				1. check if number is outside of range
					if it is outside of range move the cursor to zero and move it the remaining amounts before step 2
				2. read four bytes from obtainedd address
		*/
		if (core || info)
			ft_printf("is arg type I\n");
	}
	(*carriage)->registry[arg[1] - 1] = arg[0];
	update_carry(arg[0], carriage);
}

void	st(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[1] == R)
	{
		(*carriage)->registry[arg[1] - 1] = (*carriage)->registry[arg[0] - 1];
		ft_printf("r1: %d------------------\n", (*carriage)->registry[arg[1] - 1]);
	}
	else if ((*carriage)->arg_types[1] == I)
	{
		if (arg[1] >= 0 && arg[1] < MEM_SIZE)//check to make sure number is within range of core size
		{
			core[arg[1]] = (*carriage)->registry[arg[0] - 1];
			ft_printf("r2: %d------------------\n", core[arg[1]]);
		}
		else
		{
			ft_printf("ERRORRRRR\n");
			return ;//MAYBE SOME KIND OF ERROR HANDLING HERE??
		}
	}
	if (core || info)
		ft_printf("have core and info\n");
}

void	add(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	sum = (*carriage)->registry[arg[0] - 1] + (*carriage)->registry[arg[1] - 1];
	(*carriage)->registry[arg[2] - 1] = sum;
	update_carry(sum, carriage);
	if (core || info)
		ft_printf("have core and info\n");
}

void	sub(int arg[ARGS], uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	sum = (*carriage)->registry[arg[0] - 1] - (*carriage)->registry[arg[1] - 1];
	(*carriage)->registry[arg[2] - 1] = sum;
	update_carry(sum, carriage);
	if (core || info)
		ft_printf("have core and info\n");
}
