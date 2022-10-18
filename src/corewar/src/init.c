/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:20:09 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 16:42:41 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	sets the value of an individual carriage	*/
static void	set_values(t_carriage **new, t_profile *champ)
{
	int	i;

	i = 0;
	(*new)->id = champ->i;
	(*new)->carry = 0;
	(*new)->statement_code = 0;
	(*new)->last_live_call = -1;
	(*new)->delay = 0;
	set_arg(new);
	(*new)->pos = champ->pos;
	(*new)->registry[i++] = champ->i * -1;
	while (i < REG_NUMBER)
		(*new)->registry[i++] = 0;
}

/*
initializes the carriages by looping through each of the champs
each carriage is going to get an unique id, starting position and
value stored in registry 1 which will depend on the individual
champion
*/
static int	init_carriage(t_info **info, t_profile *champ)
{
	t_carriage	*new;
	int			j;

	j = 0;
	while (champ)
	{
		new = (t_carriage *)malloc(sizeof(t_carriage));
		if (!new)
			return (ERROR);
		set_values(&new, champ);
		new->next = (*info)->head_carriage;
		(*info)->head_carriage = new;
		(*info)->champ_names[j] = champ->name;
		champ = champ->next;
		++j;
	}
	(*info)->champ_total = j;
	return (0);
}

/*	initializing info and all of its variables	*/
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

/*	adds the champs to the core with equal spacing in between the champs	*/
static void	add_players_to_core(uint8_t core[MEM_SIZE], t_profile **champ, \
t_input **input, int count)
{
	t_profile	*prev;
	int			i;
	size_t		j;
	int			k;
	int			div;

	i = 0;
	while (i < MEM_SIZE)
		core[i++] = 0;
	div = MEM_SIZE / count;
	i = 0;
	prev = (*champ)->head;
	while (*champ)
	{
		j = 2192;
		k = div * i;
		(*champ)->pos = k;
		while (j < input[i]->current)
			core[k++] = input[i]->t_script[j++];
		++i;
		prev = *champ;
		*champ = (*champ)->next;
	}
	*champ = prev;
}

/*
reads from files and does all of the initialization before
calling the game_start function that will begin the game
*/
int	init(int argc, char **argv, int i, t_info *info)
{
	t_profile	*champ;
	t_input		**input;
	uint8_t		core[MEM_SIZE];

	champ = NULL;
	input = read_init(argc, argv, i, &champ);
	if (!input)
		return (ERROR);
	add_players_to_core(core, &champ, input, input[0]->champ_count);
	error_clean(input, NULL, input[0]->champ_count);
	if (init_info(&info, champ->head) == ERROR)
		return (error_clean(NULL, &champ, 0));
	if (game_start(core, info, champ->head) == ERROR)
		return (error_clean(NULL, &champ, 0));
	error_clean(NULL, &champ, 0);
	return (0);
}
