
#include "vm.h"

void	update_carry(int nbr, t_carriage **carriage)
{
	if (!nbr)
		(*carriage)->carry = TRUE;
	else
		(*carriage)->carry = FALSE;
}


void	v_flag4_one_arg(t_carriage **carriage, char *command)
{
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	if ((*carriage)->statement_code == 12)
	{
		ft_printf("%d ", (int16_t)(*carriage)->args_found[0]);
	}
	else if ((*carriage)->statement_code == 9)
	{
		ft_printf("%d ", (int16_t)(*carriage)->args_found[0]);
		if ((*carriage)->carry)
			ft_printf("OK\n");
		else
			ft_printf("FAILURE\n");
	}
	else if ((*carriage)->statement_code == 1)
	{
		ft_printf("%d\n", (int16_t)(*carriage)->args_found[0]);
	}
}

void	v_flag4_two_arg(t_carriage **carriage, char *command, int reg)
{
	int	i;
	int16_t temp;

	i = 0;
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	while (i < ARGS)
	{
		if (i != 0)
			ft_putchar(' ');
		if (reg == -1)
		{
			if ((*carriage)->arg_types[i] == R)
				ft_printf("r%d", (*carriage)->args_found[i]);
			else if ((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I)
			{
				temp = (int16_t)(*carriage)->args_found[i];
				ft_printf("%d", temp);
			}
		}
		else
		{
			if (i == reg)
				ft_printf("r%d", (*carriage)->args_found[i]);
			else if ((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I)
			{
				temp = (int16_t)(*carriage)->args_found[i];
				ft_printf("%d", temp);
			}
		}
		++i;
	}
	ft_putchar('\n');
}

void	zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	//int	new;
	//int	dif;

	if ((*carriage)->carry && core && info)
	{
		//new = (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD;

		int pos;
		//ft_printf("ARG FOUND: %d	car_pos: %d\n", (int16_t)(*carriage)->args_found[0], (*carriage)->pos);
		if ((int16_t)(*carriage)->args_found[0] < 0)
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[0] * -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[0] % IDX_MOD);
		
		//ft_printf("first pos: %d\n", pos);
		if (pos >= MEM_SIZE)
			pos %= MEM_SIZE;
		else if (pos < 0)
			pos = MEM_SIZE - (pos * -1);
		//ft_printf("first pos: %d\n", pos);
		(*carriage)->pos = pos;
		//new = ((*carriage)->pos + (*carriage)->args_found[0]) % MEM_SIZE;
		// if (new >= MEM_SIZE)// dont know if this is ever the case?? just thinking if number goes over memsize
		// {
		// 	dif = new - MEM_SIZE;
		// 	(*carriage)->pos = dif;
		// }
		// else
		// 	(*carriage)->pos = new;
		// //ft_printf("JUMPED EXECUTED\n");
	}
	if (info->flag[V_FLAG] == 4)
		v_flag4_one_arg(carriage, "zjmp");
}

void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	if (info->flag[V_FLAG] == 4)
		v_flag4_one_arg(carriage, "live");
	(*carriage)->last_live_call = info->total_cycles;//removed +1
	info->live_statement += 1;
	if ((*carriage)->args_found[0] == (*carriage)->registry[0] && core && info)
	{
		info->winner = (*carriage)->args_found[0] * -1;
		if (info->flag[V_FLAG] == 1)
			ft_printf("Player %d is said to be alive\n", info->winner);// decide if we want to print name of the player as well
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
	limit_jump(NULL, &pos);
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
	//ft_printf("pos: %d size: %d\n", pos, size);
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
	//ft_printf("VALUE %d\n", third);
	return (third);
}

void	ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	//ft_printf("LD LOCATED-------------------\n");
	if ((*carriage)->arg_types[0] == I && info)
	{
		if ((int16_t)(*carriage)->args_found[0] < 0)
			(*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos - (((int16_t)(*carriage)->args_found[0] * -1) % IDX_MOD), core, SIZE);
		else
			(*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos + ((int16_t)(*carriage)->args_found[0] % IDX_MOD), core, SIZE);
	}//(*carriage)->args_found[0] = read_bytes(0, (*carriage)->pos + (*carriage)->args_found[0] % IDX_MOD, core, SIZE);
	if (info->flag[V_FLAG] == 4)
		v_flag4_two_arg(carriage, "ld", ARG2);
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

	if (info->flag[V_FLAG] == 4)
		v_flag4_two_arg(carriage, "st", ARG1);
	if ((*carriage)->arg_types[1] == R)
	{
		(*carriage)->registry[(*carriage)->args_found[1] - 1] = (*carriage)->registry[(*carriage)->args_found[0] - 1];
	}
	else if ((*carriage)->arg_types[1] == I)
	{
		//ft_printf("FIND POS\n");
		//ft_printf("arg found: %d\n", (int16_t)(*carriage)->args_found[1]);
		//ft_printf("car_pos: %d\n", (*carriage)->pos);
		if ((int16_t)(*carriage)->args_found[1] < 0)
		{
			//ft_printf("minus found\n");
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[1] * -1) % IDX_MOD);
		}
		else
		//	pos = ((*carriage)->pos + (*carriage)->args_found[1]) % MEM_SIZE;
		pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[1] % IDX_MOD);
		
		//ft_printf("first pos: %d\n", pos);
		// if (pos >= MEM_SIZE)
		// 	pos %= MEM_SIZE;
		// else if (pos < 0)
		// 	pos = MEM_SIZE - (pos * -1);// i feel like this should be -1 because we don't use pos 4096... but i don't know : /
		// if (pos - (*carriage)->pos > 512)
		// 	pos = (*carriage)->pos - 512;
		// else if (pos - (*carriage)->pos < -512)
		// 	pos = (*carriage)->pos + 512;
		// if (pos >= MEM_SIZE)
		// 	pos %= MEM_SIZE;
		//ft_printf("pos: %d\n", pos);
		limit_jump(carriage, &pos);
		//ft_printf("final pos: %d\n", pos);
		
		// if ((*carriage)->id == 13)
		// 	ft_printf("pos: %d\n", pos);
		put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[0] - 1]);
		//core[pos] = (*carriage)->args_found[0];
	}
	if (!info)
		ft_printf("no info\n");
}

void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	if (info->flag[V_FLAG] == 4)
		v_flag4_two_arg(carriage, "add", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[0] - 1] + (*carriage)->registry[(*carriage)->args_found[1] - 1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!core && !info)
		ft_printf("no core and no info\n");
}

void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	if (info->flag[V_FLAG] == 4)
		v_flag4_two_arg(carriage, "sub", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[0] - 1] - (*carriage)->registry[(*carriage)->args_found[1] - 1];
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = sum;
	update_carry(sum, carriage);
	if (!core && !info)
		ft_printf("no core and no info\n");
}
