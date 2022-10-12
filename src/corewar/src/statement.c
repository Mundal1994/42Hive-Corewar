
#include "vm.h"

void	update_carry(int nbr, t_carriage **carriage)
{
	if (!nbr)
		(*carriage)->carry = TRUE;
	else
		(*carriage)->carry = FALSE;
}


int	v_flag5(t_carriage **carriage)
{
	if ((*carriage)->statement_code == OP_LIVE)
		ft_printf("LIVE (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LD)
		ft_printf("LD (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_ST)
		ft_printf("ST (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_ADD)
		ft_printf("add (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_SUB)
		ft_printf("sub (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_AND)
		ft_printf("AND (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_OR)
		ft_printf("OR (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_XOR)
		ft_printf("XOR (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_ZJMP)
		ft_printf("ZJMP (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LDI)
		ft_printf("LDI (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_STI)
		ft_printf("STI (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_FORK)
		ft_printf("FORK (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LLD)
		ft_printf("LLD (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LLDI)
		ft_printf("LLDI (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_LFORK)
		ft_printf("LFORK (%d)\n", (*carriage)->statement_code);
	else if ((*carriage)->statement_code == OP_AFF)
		ft_printf("AFF (%d)\n", (*carriage)->statement_code);
	return (TRUE);
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
	static int	found = FALSE;

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
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;
	if (info->flag[V_FLAG] == 4)
		v_flag4_one_arg(carriage, "live");
	(*carriage)->last_live_call = info->total_cycles;//removed +1
	info->live_statement += 1;
	if ((*carriage)->args_found[ARG1] >= (info->champ_total * -1) && core && info && \
		(*carriage)->args_found[ARG1] <= -1)
	{
		info->winner = (*carriage)->args_found[ARG1] * -1;
		if (info->flag[V_FLAG] == 1)
			ft_printf("Player %d (%s) is said to be alive\n", info->winner, info->champ_names[info->winner - 1]);// decide if we want to print name of the player as well
		//ft_printf("winner updated: %d\n", info->winner);
	}
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	ld(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;
	if ((*carriage)->arg_types[ARG1] == I && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] * -1) % IDX_MOD), core, SIZE);
		else
			(*carriage)->args_found[ARG1] = read_bytes(0, (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] % IDX_MOD), core, SIZE);
	}
	if (info->flag[V_FLAG] == 4)
		v_flag4_two_arg(carriage, "ld", ARG2);
	(*carriage)->registry[(*carriage)->args_found[ARG2] - 1] = (*carriage)->args_found[ARG1];
	update_carry((*carriage)->args_found[ARG1], carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
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
	static int	found = FALSE;

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
		put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	}
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	add(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	if (info->flag[V_FLAG] == 4 && core && info)
		v_flag4_three_arg(carriage, "add", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] + (*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	sub(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	sum;
	static int	found = FALSE;

	if (info->flag[V_FLAG] == 4 && core && info)
		v_flag4_three_arg(carriage, "sub", -1);
	sum = (*carriage)->registry[(*carriage)->args_found[ARG1] - 1] - (*carriage)->registry[(*carriage)->args_found[ARG2] - 1];
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = sum;
	update_carry(sum, carriage);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}
