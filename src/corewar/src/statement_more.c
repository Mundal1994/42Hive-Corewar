
#include "vm.h"

void	ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	value;
	int	pos;


	check_first_arg_type(core, carriage, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
	pos = ((*carriage)->pos + ((*carriage)->args_found[0] + (*carriage)->args_found[1])) % MEM_SIZE;
	limit_jump(carriage, &pos);
	value = read_bytes(0, pos, core, SIZE);
	//value = read_bytes(0, (*carriage)->pos + ((*carriage)->args_found[0] + (*carriage)->args_found[1]) % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = value;
	if (!info)
		ft_printf("no\n");
}

void	lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	value;

	check_first_arg_type(core, carriage, &(*carriage)->args_found[0]);
	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
	value = read_bytes(0, (*carriage)->pos + ((*carriage)->args_found[0] + (*carriage)->args_found[1]), core, SIZE);
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = value;
	if (!info)
		ft_printf("no\n");
}

void	limit_jump(t_carriage **carriage, int *pos)
{
	if (*pos - (*carriage)->pos > 512 && *pos < (*carriage)->pos)
		*pos = (*carriage)->pos - 512;
	else if (*pos - (*carriage)->pos < -512 && *pos > (*carriage)->pos)
		*pos = (*carriage)->pos + 512;
	if (*pos >= MEM_SIZE)
		*pos %= MEM_SIZE;
	// else if (*pos < 0)
	// 	*pos = MEM_SIZE - (*pos * -1);
}

void	sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	check_second_arg_type(core, carriage, &(*carriage)->args_found[1]);
	check_third_arg_type(core, carriage, &(*carriage)->args_found[2]);
	pos = ((*carriage)->pos + ((*carriage)->args_found[1] + (*carriage)->args_found[2])) % MEM_SIZE;
	ft_printf("pos : %d\n", pos);
	limit_jump(carriage, &pos);
	// if (pos - (*carriage)->pos > 512)
	// 	pos = (*carriage)->pos - 512;
	// else if (pos - (*carriage)->pos < -512)
	// 	pos = (*carriage)->pos + 512;
	// ft_printf("pos : %d\n", pos);
	// if (pos >= MEM_SIZE)
	// 	pos -= MEM_SIZE;
	// else if (pos < 0)
	// 	pos = MEM_SIZE - (pos * -1);
	ft_printf("pos : %d\n", pos);
	ft_printf("value outside putn br: %d reg: %d\n", (*carriage)->registry[(*carriage)->args_found[0] - 1], (*carriage)->args_found[0]);
	put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[0] - 1]);
	if (!info)
		ft_printf("no\n");
}

static int	copy_carriage(t_info **info, t_carriage *carriage, int new_pos)
{
	t_carriage	*new;
	int			i;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (ERROR);
	(*info)->carriage_count++;
	new->id = (*info)->carriage_count;
	new->carry = carriage->carry;
	new->statement_code = 0;
	new->last_live_call = carriage->last_live_call;
	new->delay = carriage->delay;
	new->pos =new_pos;
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
	return (0);
}

void	fork_op(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	//pos = (*carriage)->args_found[0] % IDX_MOD;
	//ft_printf("Created new CARRIAGE\n");
	pos = ((*carriage)->pos + (*carriage)->args_found[0]) % MEM_SIZE;
	// if (pos - (*carriage)->pos > 512)
	// 	pos = (*carriage)->pos - 512;
	// else if (pos - (*carriage)->pos < -512)
	// 	pos = (*carriage)->pos + 512;
	// //ft_printf("value: %d	pos: %d\n", (*carriage)->args_found[0], pos);
	// if (pos >= MEM_SIZE)
	// 	pos -= MEM_SIZE;
	limit_jump(carriage, &pos);
	//make sure position is possible
	copy_carriage(&info, *carriage, pos);
	if (!core)
		ft_printf("no fork \n");
}

void	lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	pos = (*carriage)->pos + (*carriage)->args_found[0];
	if (pos >= MEM_SIZE)
		pos -= MEM_SIZE;
	copy_carriage(&info, *carriage, pos);
	if (!core)
		ft_printf("no fork \n");
}
