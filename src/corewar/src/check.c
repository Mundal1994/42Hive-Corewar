#include "vm.h"

static void	delete_carriage(t_info *info, int id)
{
	t_carriage	*carriage;
	t_carriage	*prev;

	carriage = info->head_carriage;
	prev = NULL;
	while (carriage)
	{
		if (carriage->id == id)
		{
			if (!carriage->next && !prev)
				info->head_carriage = NULL;
			else if (!carriage->next)
				prev->next = NULL;
			else if (!prev)
				info->head_carriage = carriage->next;
			else
				prev->next = carriage->next;
			free(carriage);
			return ;
		}
		prev = carriage;
		carriage = carriage->next;
	}
}

static void	check_carriage_live_call(t_info *info)
{
	t_carriage	*carriage;
	t_carriage	*next;
	int			limit;
	
	carriage = info->head_carriage;
	if (info->cycles_to_die < 0)
		limit = info->total_cycles - 1;
	else
		limit = info->total_cycles - info->cycles_to_die - 1;
	int found = FALSE;
	//ft_printf("limit %d == %d - %d\n", limit, info->total_cycles, info->cycles_to_die);
	while (carriage)
	{
		// if (info->cycles_to_die == 836 && carriage->id == 1968)
		// {
		// 	ft_printf("carriage id: %d\n", carriage->id);
		// 	ft_printf("limit %d == %d - %d	carriage : %d in regards to limit: %d\n", limit, info->total_cycles, info->cycles_to_die, carriage->last_live_call, info->total_cycles - carriage->last_live_call);
		// 	found = TRUE;
		// }
		// if (carriage->id == 1966)
		// {
		// 	ft_printf("carriage id: %d\n", carriage->id);
		// 	ft_printf("limit %d == %d - %d	carriage : %d in regards to limit: %d\n", limit, info->total_cycles, info->cycles_to_die, carriage->last_live_call, info->total_cycles - carriage->last_live_call);
		// }
			

		//if (carriage->id == 1)
		//ft_printf("limit %d == %d - %d	carriage : %d in regards to limit: %d\n", limit, info->total_cycles, info->cycles_to_die, carriage->last_live_call, info->total_cycles - carriage->last_live_call);
		if (carriage->last_live_call <= limit)
		{
			next = carriage->next;
			if (info->flag[V_FLAG] == 8)
			{
				if (info->cycles_to_die < 0)
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", carriage->id, info->total_cycles - carriage->last_live_call - 1, info->cycles_to_die);
				else
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", carriage->id, info->total_cycles - carriage->last_live_call - 1, info->cycles_to_die);
			}
			if (carriage->id == 1093)
				found = TRUE;
			delete_carriage(info, carriage->id);
			carriage = next;
		}
		else
			carriage = carriage->next;
	}
}

static void	kill_carriages(t_info *info)
{
	check_carriage_live_call(info);
	if (info->live_statement >= NBR_LIVE)
	{
		info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
		info->checks_count = 0;//unsure about corellation of max_checks and checks_count....
		if (info->flag[V_FLAG] == 2)
			ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
	}
	else
	{
		//unsure if this is how it is supposed to be
		info->checks_count += 1;//unsure about corellation of max_checks and checks_count....
		if (info->checks_count >= MAX_CHECKS)
		{
			info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
			if (info->flag[V_FLAG] == 2)
			{
				ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
			}
			info->checks_count = 0;
		}
	}
	info->cycle_count = info->cycles_to_die;
	//ft_printf("live statement: %d\n", info->live_statement);
	info->live_statement = 0;
}

void	check(t_info *info)
{
	info->cycle_count -= 1;
	info->total_cycles += 1;
	if (info->flag[V_FLAG] == 2)
		ft_printf("It is now cycle %d\n", info->total_cycles);
	if (info->cycle_count <= 0)
		kill_carriages(info);
}
