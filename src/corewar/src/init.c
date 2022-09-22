/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:20:09 by molesen           #+#    #+#             */
/*   Updated: 2022/09/22 17:20:10 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

static int	init_carriage(t_info *info)
{
	t_carriage	*new;
	int			i;

	//while (players)
	//{
	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (-1);
	new->id = 1;//equal to player id
	new->carry = 0;
	new->statement_code = 0;
	new->last_live_call = 0;
	new->delay = 0;
	//new->pos = //current carriage position
	new->skip = 0;
	i = 0;
	while (i < REG_NUMBER)
		new->registry[i++] = 0;
	new->next = info->head;
	info->head = new;
	//}
	return (0);
}

static int	init_info(t_info *info)
{
	int	i;

	i = 0;
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (-1);
	info->winner = 0;//needs to be player with highest identification number
	info->total_cycles = 0;
	info->live_statement = 0;
	info->cycle_of_death = CYCLE_TO_DIE;
	info->checks_count = 0;
	info->head = NULL;
	if (init_carriage(info) == -1)
		return (-1);
	ft_printf("%d\n", info->head->id);
	return (0);
}

int	init(int argc, char **argv)
{
	t_info		*info;
	uint32_t	core[MEM_SIZE];
	int			i;

	info = NULL;
	//read from files - if error exit
	// loop through core and set everything to 0
	i = 0;
	while (i < MEM_SIZE)
		core[i++] = 0;
	//place players
	if (init_info(info) == -1)
		return (-1);
	// init info struct with carriage etc
	//start game
	if (argc || argv)
		return (1);
	return (0);
}


/*


initialize game play

initialize carriage
copy singular carriage and add to the beginning of the struct



*/
