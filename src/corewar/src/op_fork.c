
#include "vm.h"

static int	copy_carriage(uint8_t core[MEM_SIZE], t_info **info, t_carriage *carriage, int new_pos)
{
	t_carriage	*new;
	int			i;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (ERROR);
	(*info)->carriage_count++;
	new->id = (*info)->carriage_count;
	new->carry = carriage->carry;
	new->last_live_call = carriage->last_live_call;
	new->delay = 0;
	new->pos =new_pos;
	new->statement_code = OP_NULL;
	new->home = carriage->home;//this should probably be different
	new->current = carriage->current;//this should probably be different
	new->skip = carriage->skip;//not using skip
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

	if (print_command(info) == TRUE && core)
		v_flag4_one_arg(carriage, "fork");
	sum = (int16_t)(*carriage)->args_found[ARG1];
	if (sum < 0)
		pos = (*carriage)->pos - ((sum * -1) % IDX_MOD);
	else
		pos = (*carriage)->pos + (sum % IDX_MOD);
	if (print_command(info) == TRUE)
		ft_printf("(%d)\n", pos);
	limit_jump(&pos);
	//ft_printf("from car %d [%d] -> %d [%d]\n", (*carriage)->id, (*carriage)->pos, info->carriage_count + 1, pos);
	copy_carriage(core, &info, *carriage, pos);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}

void	lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;
	static int	found = FALSE;

	if (print_command(info) == TRUE && core)
		v_flag4_one_arg(carriage, "lfork");
	pos = (*carriage)->pos + (int16_t)(*carriage)->args_found[ARG1];
	if (print_command(info) == TRUE)
		ft_printf("(%d)\n", pos);
	limit_jump(&pos);
	copy_carriage(core, &info, *carriage, pos);
	if (info->flag[V_FLAG] == 25 && found == FALSE)
		found = v_flag5(carriage);
}
