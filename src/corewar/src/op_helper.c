#include "vm.h"

void	update_carry(int nbr, t_carriage **carriage)
{
	if (!nbr)
		(*carriage)->carry = TRUE;
	else
		(*carriage)->carry = FALSE;
}

void	put_nbr(uint8_t core[MEM_SIZE], int pos, uint32_t nbr)
{
	uint32_t	value;
	uint32_t	result;
	int	j;

	value = nbr;
	j = 3;
	//ft_printf("VALUE---%llu\n", nbr);
	while (j >= 0)
	{
		//ft_printf("result %i\n", (value % 16) * ft_pow(16, 0));
		result = (value % 16) * ft_pow(16, 0);
		value /= 16;
		//ft_printf("result %i\n", (value % 16) * ft_pow(16, 1));
		result += (value % 16) * ft_pow(16, 1);
		value /= 16;
		if (pos + j >= MEM_SIZE)
			core[(pos + j) - MEM_SIZE] = result;
		else
			core[pos + j] = result;
		//ft_printf("CHECK------ %i   pso %d    orig %i\n", core[pos + j], pos + j, pos);
		j--;
	}
}

void	limit_jump(int *pos)
{
	if (*pos >= MEM_SIZE)
	{
		//ft_printf("updated pos1: prev pos %d %% MEM_SSIZE(%d) = ", *pos, MEM_SIZE);
		*pos %= MEM_SIZE;
		//ft_printf("%d\n", *pos);
	}
	else if (*pos < 0)
	{
		*pos = MEM_SIZE - (*pos * -1);
		//ft_printf("updated pos2\n");
	}
}

void	update_arg_values(uint8_t core[MEM_SIZE], t_carriage **carriage, int64_t *arg, int count)
{
	if ((*carriage)->arg_types[count] == R)
		*arg = (*carriage)->registry[*arg - 1];
	else if ((*carriage)->arg_types[count] == I)
	{
		if (*arg < 0)
			*arg = read_bytes(0, (*carriage)->pos - ((*arg * -1) % IDX_MOD), core, SIZE);
		else
			*arg = read_bytes(0, (*carriage)->pos + (*arg % IDX_MOD), core, SIZE);
	}
}
