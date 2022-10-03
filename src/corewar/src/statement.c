
#include "vm.h"

void	update_carry(int nbr, t_carriage **carriage)
{
	if (!nbr)
		(*carriage)->carry = TRUE;
	else
		(*carriage)->carry = FALSE;
}

void	zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	new;
	int	dif;

	if ((*carriage)->carry && core && info)
	{
		new = (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD;
		if (new >= MEM_SIZE)// dont know if this is ever the case?? just thinking if number goes over memsize
		{
			dif = new - MEM_SIZE;
			(*carriage)->pos = dif;
		}
		else
			(*carriage)->pos = new;
	}
}

void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	(*carriage)->last_live_call = info->total_cycles + 1;
	if ((*carriage)->args_found[0] == (*carriage)->registry[0] && core && info)
	{
		info->winner = (*carriage)->args_found[0] * -1;
		ft_printf("winner updated: %d\n", info->winner);
	}
}

int		read_bytes(u_int32_t third, int	pos, uint8_t core[MEM_SIZE], int size)
{
	int	i;
	int	hold;
	int	j;
	//int	third;
	int	type;

	i = 0;
	ft_printf("pos: %d\n", pos);
	if (third == 2 || third == 0)
	{
		type = size;//info->operations[SIZE][carriage->statement_code - 1];
		j = (size * 2) - 1;
	}
	else
	{
		type = 2;
		j = 3;
	}
	//++carriage->tmp_pos;
	third = 0;
	ft_printf("size: %d	pos: %d\n", size, core[pos]);
	ft_printf("pos: %d\n", core[pos + 1]);
	ft_printf("pos: %d\n", core[pos + 2]);
	ft_printf("pos: %d\n", core[pos + 3]);
	while (i < type)//info->operations[SIZE][carriage->statement_code - 1])
	{
		ft_printf("%i < %d\n", i, type);
		if ((pos + i) >= MEM_SIZE)
			pos = (pos % MEM_SIZE) - i;
		ft_printf("pos: %d\n", pos);
		hold = core[pos + i];
		third += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		third += (hold % 16) * ft_pow(16, j--);
		++i;
	}
	return (third);
}
// now i have registry 1 as 0  and 1 as 2... could also add 17 registry and have the first as a null and never use it??

void	ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	ft_printf("LD LOCATED-------------------\n");
	if ((*carriage)->arg_types[0] == I)
	{
		// READ BYTE IN OTHER POSITION OF THE MEM_SIZE to calculate new (*carriage)->args_found[0]
		//just update (*carriage)->args_found[0]
		// function that reads four bytes (or 2) from obtained address
		/*
			ex
						pos									core	size (if it is 1 or 2)
			read_bytes((*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD, core, info->operations[IDX_LD][SIZE]);
				1. check if number is outside of range
					if it is outside of range move the cursor to zero and move it the remaining amounts before step 2
				2. read four bytes from obtainedd address
		*/
		(*carriage)->statement_code = 1 + 1;//delete this after testing is done
		ft_printf("size: %d\n", info->operations[SIZE][(*carriage)->statement_code - 1]);
		(*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
		if (core || info)
			ft_printf("is arg type I\n");
	}
	(*carriage)->registry[(*carriage)->args_found[1] - 1] = (*carriage)->args_found[0];
	update_carry((*carriage)->args_found[0], carriage);
}

void	st(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if ((*carriage)->arg_types[1] == R)
	{
		(*carriage)->registry[(*carriage)->args_found[1] - 1] = (*carriage)->registry[(*carriage)->args_found[0] - 1];
		ft_printf("r1: %d------------------\n", (*carriage)->registry[(*carriage)->args_found[1] - 1]);
	}
	else if ((*carriage)->arg_types[1] == I)
	{
		if ((*carriage)->args_found[1] >= 0 && (*carriage)->args_found[1] < MEM_SIZE)//check to make sure number is within range of core size
		{
			core[(*carriage)->args_found[1]] = (*carriage)->registry[(*carriage)->args_found[0] - 1];
			ft_printf("r2: %d------------------\n", core[(*carriage)->args_found[1]]);
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

void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	sum = (*carriage)->registry[(*carriage)->args_found[0] - 1] + (*carriage)->registry[(*carriage)->args_found[1] - 1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (core || info)
		ft_printf("have core and info\n");
}

void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	sum = (*carriage)->registry[(*carriage)->args_found[0] - 1] - (*carriage)->registry[(*carriage)->args_found[1] - 1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (core || info)
		ft_printf("have core and info\n");
}
