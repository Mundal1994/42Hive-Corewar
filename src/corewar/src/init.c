/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:20:09 by molesen           #+#    #+#             */
/*   Updated: 2022/09/27 11:35:07 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	init_carriage(t_info **info, t_profile *champ)
{
	t_carriage	*new;
	int			i;

	while (champ)
	{
		new = (t_carriage *)malloc(sizeof(t_carriage));
		if (!new)
			return (ERROR);
		new->id = champ->i;
		new->carry = 0;
		new->statement_code = 0;
		new->last_live_call = 0;
		new->delay = 0;
		new->pos = champ->pos;
		new->skip = 0;
		i = 0;
		// reg_1 = - player_id	NEEDS TO STILL FIX LOGIC OF THE REGISTRYS
		while (i < REG_NUMBER)
			new->registry[i++] = 0;
		new->next = (*info)->head_carriage;
		(*info)->head_carriage = new;
		champ = champ->next;
	}
	return (0);
}

static int	init_info(t_info **info, t_profile *champ)
{
	int	i;

	i = 0;
	*info = (t_info *)malloc(sizeof(t_info));
	if (!(*info))
		return (ERROR);
	(*info)->total_cycles = 0;
	(*info)->live_statement = 0;
	(*info)->cycles_to_die = CYCLE_TO_DIE;
	(*info)->cycle_count = CYCLE_TO_DIE;
	(*info)->checks_count = 0;
	(*info)->head_carriage = NULL;
	if (init_carriage(info, champ) == ERROR)
		return (ERROR);
	(*info)->winner = (*info)->head_carriage->id;
	(*info)->carriage_count = (*info)->head_carriage->id;
	return (0);
}

static void	add_players_to_core(uint32_t core[MEM_SIZE], t_profile **champ, t_input **input, int count)
{
	t_profile *head;
	int			i;
	size_t		j;
	int			k;
	int			div;

	i = 0;
	while (i < MEM_SIZE)
		core[i++] = 0;
	div = MEM_SIZE / count;
	i = 0;
	head = (*champ)->head;
	while (*champ)
	{
		j = 2192;
		k = div * i;
		(*champ)->pos = k;
		while (j < input[i]->current)
			core[k++] = input[i]->t_script[j++];
		++i;
		*champ = (*champ)->next;
	}
	*champ = head;
}

int	init(int argc, char **argv, int i)
{
	t_info		*info;
	t_profile	*champ;
	t_input		**input;
	uint32_t	core[MEM_SIZE];

	info = NULL;
	champ = NULL;
	input = read_init(argc, argv, i, &champ);
	if (!input)
		return (ERROR);
	add_players_to_core(core, &champ, input, argc - i);
	// doens't use input anymore after this point
	if (init_info(&info, champ) == ERROR)
		return (ERROR);//free info and champ here before exiting
	if (game_start(core, info, champ) == ERROR)
		return (ERROR);//free info and champ here before exiting
	return (0);
}
