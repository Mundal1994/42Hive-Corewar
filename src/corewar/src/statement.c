
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
	if ((*carriage)->statement_code == OP_FORK || (*carriage)->statement_code == OP_LFORK)
		ft_printf("%d ", (int16_t)(*carriage)->args_found[ARG1]);
	else if ((*carriage)->statement_code == OP_ZJMP)
	{
		ft_printf("%d ", (int16_t)(*carriage)->args_found[ARG1]);
		if ((*carriage)->carry)
			ft_printf("OK\n");
		else
			ft_printf("FAILED\n");
	}
	else if ((*carriage)->statement_code == OP_LIVE)
		ft_printf("%d\n", (*carriage)->args_found[ARG1]);
}

void	v_flag4_two_arg(t_carriage **carriage, char *command, int reg)
{
	int	i;

	i = 0;
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	while (i < ARG3)
	{
		if (i != 0)
			ft_putchar(' ');
		// if (reg == -1)
		// {
		// 	if ((*carriage)->arg_types[i] == R)
		// 		ft_printf("r%d", (*carriage)->args_found[i]);
		// 	else if ((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I)
		// 		ft_printf("%d", (int16_t)(*carriage)->args_found[i]);
		// }
		// else
		// {
			if (i == reg)
				ft_printf("r%d", (*carriage)->args_found[i]);
			else if (((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I) && \
				(*carriage)->statement_code == OP_LD)
				ft_printf("%d", (*carriage)->args_found[i]);
			// else if (((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I) && \
			// 	(*carriage)->statement_code == OP_LLD)
			// 	ft_printf("%d", (*carriage)->args_found[i]);NEED TO COME BACK TO THIS
			else if ((*carriage)->arg_types[i] == D || (*carriage)->arg_types[i] == I)
				ft_printf("%d", (int16_t)(*carriage)->args_found[i]);
		//}
		++i;
	}
	ft_putchar('\n');
}

void	zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	if ((*carriage)->carry && core && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] * -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] % IDX_MOD);
		limit_jump(&pos);
		(*carriage)->pos = pos;
	}
	if (info->flag[V_FLAG] == 4)
		v_flag4_one_arg(carriage, "zjmp");
}

void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	// if ((*carriage)->id == 14)
	// 	ft_printf("CARRIAGE 4 ENTERED LIVE\n");
	if (info->flag[V_FLAG] == 4)
		v_flag4_one_arg(carriage, "live");
	(*carriage)->last_live_call = info->total_cycles;//removed +1
	info->live_statement += 1;
	if ((*carriage)->args_found[ARG1] == (*carriage)->registry[0] && core && info && \
		(*carriage)->registry[0] >= -4 && (*carriage)->registry[0] <= -1)
	{
		info->winner = (*carriage)->args_found[ARG1] * -1;
		if (info->flag[V_FLAG] == 1)
			ft_printf("Player %d is said to be alive\n", info->winner);// decide if we want to print name of the player as well
		//ft_printf("winner updated: %d\n", info->winner);
	}
}

int		read_bytes(u_int32_t third, int	pos, uint8_t core[MEM_SIZE], int size)
{
	int	i;
	int	hold;
	int	j;
	int	type;

	i = 0;
	limit_jump(&pos);
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
	if ((*carriage)->arg_types[ARG1] == I && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] * -1) % IDX_MOD), core, SIZE);
		else
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] % IDX_MOD), core, SIZE);
	}
	if (info->flag[V_FLAG] == 4)
		v_flag4_two_arg(carriage, "ld", ARG2);
	// if ((*carriage)->id == 1)
	// {
	// 	print_core(core, info);
	// 	ft_printf("car->pos: %d	cycle_count: %d\n", (*carriage)->pos, info->total_cycles);
	// 	ft_printf("r%d: new value: %d\n", (*carriage)->args_found[ARG2], (*carriage)->args_found[ARG1]);
	// 	ft_printf("r10: %d\n", (*carriage)->registry[9]);

	// }
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->args_found[ARG1];
	update_carry((*carriage)->args_found[ARG1], carriage);
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

	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_two_arg(carriage, "st", ARG1);
	if ((*carriage)->arg_types[ARG2] == R)
		(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1];
	else if ((*carriage)->arg_types[ARG2] == I)
	{
		if ((int16_t)(*carriage)->args_found[ARG2] < 0)
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG2] * -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG2] % IDX_MOD);
		limit_jump(&pos);
		// if ((*carriage)->id == 14 && info->total_cycles == 8908)
		// ft_printf("carriage->pos: %d	put nbr at pos: %d	orignbr: %d	nbrput: %d\n", (*carriage)->pos, pos, (int16_t)(*carriage)->args_found[ARG2], (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
		put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	}
}

void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	if (info->flag[V_FLAG] == 4 && core && info)
		v_flag4_three_arg(carriage, "add", -1);
		//v_flag4_two_arg(carriage, "add", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] + (*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
}

void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;

	if (info->flag[V_FLAG] == 4 && core && info)
		v_flag4_three_arg(carriage, "sub", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] - (*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
}
