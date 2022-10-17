/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:20:09 by molesen           #+#    #+#             */
/*   Updated: 2022/09/29 13:10:45 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	init_carriage(t_info **info, t_profile *champ)
{
	t_carriage	*new;
	int			i;
	int			j;

	j = 0;
	while (champ)
	{
		new = (t_carriage *)malloc(sizeof(t_carriage));
		if (!new)
			return (ERROR);
		new->id = champ->i;
		new->carry = 0;
		new->statement_code = 0;
		new->last_live_call = -1;
		new->delay = 0;
		new->pos = champ->pos;
		i = 0;
		new->registry[i++] = champ->i * -1;
		while (i < REG_NUMBER)
			new->registry[i++] = 0;
		set_arg(&new);
		new->next = (*info)->head_carriage;
		(*info)->head_carriage = new;
		(*info)->champ_names[j] = champ->name;
		champ = champ->next;
		++j;
	}
	(*info)->champ_total = j;
	return (0);
}

static int	init_info(t_info **info, t_profile *champ)
{
	int	i;

	i = 0;
	(*info)->total_cycles = 1;
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

static void	add_players_to_core(uint8_t core[MEM_SIZE], t_profile **champ, t_input **input, int count)
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

int	init(int argc, char **argv, int i, t_info *info)
{
	t_profile	*champ;
	t_input		**input;
	uint8_t	core[MEM_SIZE];

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
