
#include "vm.h"

void	limit_jump(int *pos)
{
	if (*pos >= MEM_SIZE)
		*pos %= MEM_SIZE;
	else if (*pos < 0)
		*pos = MEM_SIZE - (*pos * -1);
}

void	v_flag4_three_arg(t_carriage **carriage, char *command, int reg)
{
	int	i;

	i = 0;
	ft_printf("P %4d | %s ", (*carriage)->id, command);
	while (i < ARGS)
	{
		if (i != 0)
			ft_putchar(' ');
		if (reg == -1)
		{
			ft_printf("r%d", (*carriage)->args_found[i]);
		}
		else
		{
			if (i == reg)
				ft_printf("r%d", (*carriage)->args_found[i]);
			else
				ft_printf("%d", (*carriage)->args_found[i]);
		}
		++i;
	}
	ft_putchar('\n');
}

void	ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		value;
	int		pos;
	int16_t sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "ldi", ARG3);
	sum = (int16_t)(*carriage)->args_found[ARG1] + (int16_t)(*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
		if (info->flag[V_FLAG] == 4)
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG1], (int16_t)(*carriage)->args_found[ARG2], sum, pos);
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = value;
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	value;
	int	pos;
	int	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG1], ARG1);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "lldi", ARG3);
	sum = (*carriage)->args_found[ARG1] + (*carriage)->args_found[ARG2];
	if (sum < 0)
		pos = (*carriage)->pos - (sum * -1);
	else
		pos = (*carriage)->pos + sum;
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", (*carriage)->args_found[ARG1], (*carriage)->args_found[ARG2], sum, pos);
	limit_jump(&pos);
	value = read_bytes(0, pos, core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[ARG3] - 1] = value;
	update_carry(value, carriage);//one place it said that this function contrary to lld should update carry
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		pos;
	int16_t	sum;
	static int	found = FALSE;

	update_arg_values(core, carriage, &(*carriage)->args_found[ARG2], ARG2);
	update_arg_values(core, carriage, &(*carriage)->args_found[ARG3], ARG3);
	if (info->flag[V_FLAG] == 4 && info)
		v_flag4_three_arg(carriage, "sti", ARG1);
	sum = (int16_t)(*carriage)->args_found[ARG2] + (int16_t)(*carriage)->args_found[ARG3];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if (info->flag[V_FLAG] == 4)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", (int16_t)(*carriage)->args_found[ARG2], (int16_t)(*carriage)->args_found[ARG3], sum, pos);
	limit_jump(&pos);
	put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[ARG1] - 1]);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

// static void	init_op_table(op_table *op_table[STATE])
// {
// 	int	i;

// 	i = 0;
// 	op_table[i++] = live;
// 	op_table[i++] = ld;
// 	op_table[i++] = st;
// 	op_table[i++] = add;
// 	op_table[i++] = sub;
// 	op_table[i++] = and;
// 	op_table[i++] = or;
// 	op_table[i++] = xor;
// 	op_table[i++] = zjmp;
// 	op_table[i++] = ldi;
// 	op_table[i++] = sti;
// 	op_table[i++] = fork_op;
// 	op_table[i++] = lld;
// 	op_table[i++] = lldi;
// 	op_table[i++] = lfork;
// 	op_table[i++] = aff;
// }

static int	copy_carriage(uint8_t core[MEM_SIZE], t_info **info, t_carriage *carriage, int new_pos)
{
	t_carriage	*new;
	int			i;
	//op_table	*op_table[STATE];//copied from game start

	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (ERROR);
	(*info)->carriage_count++;
	new->id = (*info)->carriage_count;
	//if (new->id == 1968 || new->id == 1966)
	//	ft_printf("id: %d", carriage->id);
	new->carry = carriage->carry;
	new->last_live_call = carriage->last_live_call;
	new->delay = 0;
	new->pos =new_pos;
	new->statement_code = OP_NULL;
	// set_statement_code(core, &new, *info);
	// if (new->delay >= 1)
	// 	new->delay -= 1;
	// if (new->delay == 0)
	// {
	// 	init_op_table(op_table);
	// 	perform_statement_code(core, &new, *info, op_table);
	// 	carriage->statement_code = OP_NULL;
	// }
	new->home = carriage->home;//this should probably be different
	new->current = carriage->current;//this should probably be different
	new->skip = carriage->skip;//this should probably be different
	i = -1;
	while (++i < REG_NUMBER)
		new->registry[i] = carriage->registry[i];
	i = 0;
	while (i < 3)
	{
		new->arg_types[i] = 0;
		new->args_found[i++] = 0;
	}
	new->next = (*info)->head_carriage;
	(*info)->head_carriage = new;
	if (core)
		return (0);
	return (0);
}

void	fork_op(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int		pos;
	int16_t	sum;
	static int	found = FALSE;

	if (info->flag[V_FLAG] == 4 && core)
		v_flag4_one_arg(carriage, "fork");
	sum = (int16_t)(*carriage)->args_found[ARG1];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if (info->flag[V_FLAG] == 4)
		ft_printf("(%d)\n", pos);
	limit_jump(&pos);
	//ft_printf("from car %d [%d] -> %d [%d]\n", (*carriage)->id, (*carriage)->pos, info->carriage_count + 1, pos);
	copy_carriage(core, &info, *carriage, pos);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}

void	lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;
	static int	found = FALSE;

	if (info->flag[V_FLAG] == 4 && core)
		v_flag4_one_arg(carriage, "lfork");
	pos = (*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1];
	if (info->flag[V_FLAG] == 4)
		ft_printf("(%d)\n", pos);
	limit_jump(&pos);
	copy_carriage(core, &info, *carriage, pos);
	if (info->flag[V_FLAG] == 5 && found == FALSE)
		found = v_flag5(carriage);
}
