
#include "vm.h"

void	ldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	value;

	check_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	value = read_bytes(0, (*carriage)->pos + ((*carriage)->args_found[0] + (*carriage)->args_found[1]) % IDX_MOD, core, info->operations[SIZE][(*carriage)->statement_code - 1]);
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = value;
	if (core || carriage || info)
		ft_printf("ldi rocks\n");
}

void	lldi(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	value;

	check_arg_type(core, carriage, info, &(*carriage)->args_found[0]);
	check_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	value = read_bytes(0, (*carriage)->pos + ((*carriage)->args_found[0] + (*carriage)->args_found[1]), core, info->operations[SIZE][(*carriage)->statement_code - 1]);
	(*carriage)->registry[(*carriage)->args_found[2] - 1] = value;
	if (core || carriage || info)
		ft_printf("ldi rocks\n");
}

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
error with this function - example can be found with this command!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	./corewar -d 100 champs/examples/bigzork.cor champs/examples/zork.cor
*/
void	sti(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	check_arg_type(core, carriage, info, &(*carriage)->args_found[1]);
	check_arg_type(core, carriage, info, &(*carriage)->args_found[2]);
	pos = (*carriage)->pos + ((*carriage)->args_found[1] + (*carriage)->args_found[2]) % IDX_MOD;
	if (pos >= MEM_SIZE)
		pos -= MEM_SIZE;
	put_nbr(core, pos, (uint32_t)(*carriage)->registry[(*carriage)->args_found[0] - 1]);
	//core[pos] = (*carriage)->registry[(*carriage)->args_found[0] - 1];
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

	pos =  (*carriage)->args_found[0] % IDX_MOD;
	if (pos >= MEM_SIZE)
		pos -= MEM_SIZE;
	//make sure position is possible
	copy_carriage(&info, *carriage, pos);
	if (core)
		ft_printf("fork \n");
}

void	lfork(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int	pos;

	pos = (*carriage)->pos + (*carriage)->args_found[0];
	if (pos >= MEM_SIZE)
		pos -= MEM_SIZE;
	copy_carriage(&info, *carriage, pos);
	if (core)
		ft_printf("fork \n");
}
