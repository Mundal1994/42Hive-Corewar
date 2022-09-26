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

static int	init_carriage(t_info **info)
{
	t_carriage	*new;
	int			i;

	//while (players)
	//{
	new = (t_carriage *)malloc(sizeof(t_carriage));
	if (!new)
		return (ERROR);
	new->id = 1;//equal to player id
	new->carry = 0;
	new->statement_code = 0;
	new->last_live_call = 0;
	new->delay = 0;
	//new->pos = //current carriage position
	new->pos = 0;
	new->skip = 0;
	i = 0;
	// reg_1 = - player_id
	while (i < REG_NUMBER)
		new->registry[i++] = 0;
	new->next = (*info)->head;
	(*info)->head = new;
	//}
	return (0);
}

static int	init_info(t_info **info)
{
	int	i;

	i = 0;
	*info = (t_info *)malloc(sizeof(t_info));
	if (!(*info))
		return (ERROR);
	(*info)->total_cycles = 0;
	(*info)->live_statement = 0;
	(*info)->cycle_of_death = CYCLE_TO_DIE;
	(*info)->death_count = CYCLE_TO_DIE;
	(*info)->checks_count = 0;
	(*info)->head = NULL;
	if (init_carriage(info) == ERROR)
		return (ERROR);
	(*info)->winner = (*info)->head->id;
	return (0);
}

void	print_core(uint32_t core[MEM_SIZE])
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (core[i] < 16)
			ft_printf("0%x", core[i]);
		else
			ft_printf("%x", core[i]);
		++line;
		++i;
		if (line >= 64)
		{
			ft_printf("\n");
			line = 0;
			if (i >= MEM_SIZE)
				break ;
			ft_printf("%#0.4x : ", i);
		}
		else
			ft_printf(" ");
	}
}

static void	add_zork(uint32_t core[MEM_SIZE])
{
	int i = 0;
	core[i++] = 11;
	core[i++] = 104;
	core[i++] = 1;
	core[i++] = 0;
	core[i++] = 15;
	core[i++] = 0;
	core[i++] = 1;
	core[i++] = 6;
	core[i++] = 100;
	core[i++] = 1;
	core[i++] = 0;
	core[i++] = 0;
	core[i++] = 0;
	core[i++] = 0;
	core[i++] = 1;
	core[i++] = 1;
	core[i++] = 0;
	core[i++] = 0;
	core[i++] = 0;
	core[i++] = 1;
	core[i++] = 9;
	core[i++] = 255;
	core[i++] = 251;
}

int	init(int argc, char **argv, int i)
{
	t_info		*info;
	t_profile	**champ;
	uint32_t	core[MEM_SIZE];
	int			j;

	info = NULL;
	champ = NULL;
	//read from files - if error exit
	// loop through core and set everything to 0
	if (read_init(argc, argv, i, champ) == ERROR)
		return (ERROR);
	j = 0;
	while (j < MEM_SIZE)
		core[j++] = 0;
	add_zork(core);
	print_core(core);
	//place players
	if (init_info(&info) == ERROR)//add player struct
		return (ERROR);
	if (game_start(core, info) == ERROR)//add player struct
		return (ERROR);
	if (argc || argv)
		return (1);
	return (0);
}
