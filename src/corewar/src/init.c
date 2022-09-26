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

static int	init_carriage(t_info **info, t_profile **champ)
{
	t_carriage	*new;
	int			i;

	while (*champ)
	{
		new = (t_carriage *)malloc(sizeof(t_carriage));
		if (!new)
			return (ERROR);
		new->id = (*champ)->i + 1;//equal to player id
		new->carry = 0;
		new->statement_code = 0;
		new->last_live_call = 0;
		new->delay = 0;
		//new->pos = //current carriage position
		new->pos = (*champ)->pos;
		new->skip = 0;
		i = 0;
		// reg_1 = - player_id
		while (i < REG_NUMBER)
			new->registry[i++] = 0;
		new->next = (*info)->head_carriage;
		(*info)->head_carriage = new;
		*champ = (*champ)->next;
	}
	return (0);
}

static int	init_info(t_info **info, t_profile **champ)
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
	(*info)->head_carriage = NULL;
	if (init_carriage(info, champ) == ERROR)
		return (ERROR);
	(*info)->winner = (*info)->head_carriage->id;
	(*info)->carriage_count = (*info)->head_carriage->id;
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

static void	add_players_to_core(uint32_t core[MEM_SIZE], t_profile **champ, t_input **input, int count)
{
	t_profile	*head;
	int			i;
	int			j;
	int			k;
	int			div;

	i = 0;
	while (i < MEM_SIZE)
		core[i++] = 0;
	div = MEM_SIZE / count;
	head = *champ;
	i = 0;
	while (*champ)
	{
		j = 2192;
		k = div * i;
		(*champ)->pos = k;
		//while (j < input[i]->current)??????
		while (input[i]->t_script[j])
			core[k++] = input[i]->t_script[j++];
		++i;
		*champ = (*champ)->next;
	}
	*champ = head;
}

int	init(int argc, char **argv, int i)
{
	t_info		*info;
	t_profile	**champ;
	t_input		**input;
	uint32_t	core[MEM_SIZE];

	info = NULL;
	champ = NULL;
	input = read_init(argc, argv, i, champ);//free champ and input from inside this function
	if (!input)
		return (ERROR);
	// if (champ[0])
	// 	ft_printf("name: %d\n", champ[0]->i);
	//ft_printf("name: %s\n", champ[0]->name);
	//ft_printf("comment: %s\n", champ[0]->comment);
	//ft_printf("exec code: %d\n", champ[0]->exec_cd_sz);
	//ft_printf("%s\n", input[0]->t_script[champ[0]->exec_cd_sz]);
	add_players_to_core(core, champ, input, argc - i);//need to modify and return champ
	// doens't use input anymore after this point
	print_core(core);
	//place players
	if (init_info(&info, champ) == ERROR)//don't have to return modification of champ
		return (ERROR);//free info and champ here before exiting
	if (game_start(core, info, champ) == ERROR)//don't have to return modification of champ
		return (ERROR);//free info and champ here before exiting
	return (0);
}
