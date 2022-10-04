
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
		//new = (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD;
		new = ((*carriage)->pos + (*carriage)->args_found[0]) % MEM_SIZE;
		if (new >= MEM_SIZE)// dont know if this is ever the case?? just thinking if number goes over memsize
		{
			dif = new - MEM_SIZE;
			(*carriage)->pos = dif;
		}
		else
			(*carriage)->pos = new;
		//ft_printf("JUMPED EXECUTED\n");
	}
}

void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	(*carriage)->last_live_call = info->total_cycles + 1;
	if ((*carriage)->args_found[0] == (*carriage)->registry[0] && core && info)
	{
		info->winner = (*carriage)->args_found[0] * -1;
		//ft_printf("winner updated: %d\n", info->winner);
	}
	//ft_printf("LIVE EXECUTED\n");
}

int		read_bytes(u_int32_t third, int	pos, uint8_t core[MEM_SIZE], int size)
{
	int	i;
	int	hold;
	int	j;
	int	type;

	i = 0;
	if (third == 2 || third == 0)
	{
		type = size;
		j = (size * 2) - 1;
	}
	else
	{
		type = 2;
		j = 3;
	}
	third = 0;
	while (i < type)
	{
		if ((pos + i) >= MEM_SIZE)
			pos = (pos % MEM_SIZE) - i;
		hold = core[pos + i];
		third += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		third += (hold % 16) * ft_pow(16, j--);
		++i;
	}
	return (third);
}

void	ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	//ft_printf("LD LOCATED-------------------\n");
	if ((*carriage)->arg_types[0] == I)
		(*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
	(*carriage)->registry[(*carriage)->args_found[1] - 1] = (*carriage)->args_found[0];
	update_carry((*carriage)->args_found[0], carriage);
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

void	st(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	if ((*carriage)->arg_types[1] == R)
	{
		(*carriage)->registry[(*carriage)->args_found[1] - 1] = (*carriage)->registry[(*carriage)->args_found[0] - 1];
	}
	else if ((*carriage)->arg_types[1] == I)
	{
		pos = ((*carriage)->pos + (*carriage)->args_found[1]) % MEM_SIZE;
		if (pos >= MEM_SIZE)
			pos %= MEM_SIZE;
		put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[0] - 1]);
		//core[pos] = (*carriage)->args_found[0];
	}
	if (!info)
		ft_printf("no info\n");
}

void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	sum = (*carriage)->registry[(*carriage)->args_found[0] - 1] + (*carriage)->registry[(*carriage)->args_found[1] - 1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!core && !info)
		ft_printf("no core and no info\n");
}

void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	sum = (*carriage)->registry[(*carriage)->args_found[0] - 1] - (*carriage)->registry[(*carriage)->args_found[1] - 1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!core && !info)
		ft_printf("no core and no info\n");
}
