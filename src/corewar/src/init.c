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

static int	init_carriage(uint8_t core[MEM_SIZE], t_info **info, t_profile *champ)
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
		new->home = &core[0];
		new->current = &core[new->pos];
		new->skip = 0;
		i = 0;
		new->registry[i++] = champ->i * -1;
		// reg_1 = - player_id	NEEDS TO STILL FIX LOGIC OF THE REGISTRYS
		/*
		r1 == registry[0]
		r2 == registry[1]
		*/
		while (i < REG_NUMBER)
			new->registry[i++] = 0;
		new->next = (*info)->head_carriage;
		(*info)->head_carriage = new;
		champ = champ->next;
	}
	return (0);
}
static void type_code(t_info **info)
{
	int		i;
	int		j;
	char	*dir;
	char	*pcb;
	char	*arg1;

	i = 0;
	j = 0;
	dir = "4 4 4 4 4 4 4 4 2 2 2 2 4 2 2 4";
	pcb = "0 1 1 1 1 1 1 1 0 1 1 0 1 1 0 1";
	arg1 = "2 6 1 1 1 7 7 7 2 7 1 2 6 7 2 1";
	while (i < STATE)
	{
		(*info)->operations[SIZE][i] = dir[j] - '0';
		(*info)->operations[PCB][i] = pcb[j] - '0';
		(*info)->operations[ARG1][i] = arg1[j] - '0';
		++i;
		j += 2;
	}
}

static void	statment_delay(t_info **info)
{
	int		i;
	int		j;
	char	*arg2;
	char	*arg3;

	i = 0;
	j = 0;
	arg2 = "0 1 5 1 1 7 7 7 0 4 7 0 1 4 0 0";
	arg3 = "0 0 0 1 1 1 1 1 0 1 4 0 0 1 0 0";
	while (i < STATE)
	{
		(*info)->operations[ARG2][i] = arg2[j] - '0';
		(*info)->operations[ARG3][i] = arg3[j] - '0';
		++i;
		j += 2;
	}
	i = 0;
	(*info)->operations[DELAY][i++] = 10;
	(*info)->operations[DELAY][i++] = 5;
	(*info)->operations[DELAY][i++] = 5;
	(*info)->operations[DELAY][i++] = 10;
	(*info)->operations[DELAY][i++] = 10;
	(*info)->operations[DELAY][i++] = 6;
	(*info)->operations[DELAY][i++] = 6;
	(*info)->operations[DELAY][i++] = 6;
	(*info)->operations[DELAY][i++] = 20;
	(*info)->operations[DELAY][i++] = 25;
	(*info)->operations[DELAY][i++] = 25;
	(*info)->operations[DELAY][i++] = 800;
	(*info)->operations[DELAY][i++] = 10;
	(*info)->operations[DELAY][i++] = 50;
	(*info)->operations[DELAY][i++] = 1000;
	(*info)->operations[DELAY][i++] = 2;
	type_code(info);
}

static int	init_info(uint8_t core[MEM_SIZE], t_info **info, t_profile *champ)
{
	int	i;

	i = 0;
	(*info)->total_cycles = 0;
	(*info)->live_statement = 0;
	(*info)->cycles_to_die = CYCLE_TO_DIE;
	(*info)->cycle_count = CYCLE_TO_DIE;
	(*info)->checks_count = 0;
	(*info)->head_carriage = NULL;
	if (init_carriage(core, info, champ) == ERROR)
		return (ERROR);
	(*info)->winner = (*info)->head_carriage->id;
	(*info)->carriage_count = (*info)->head_carriage->id;
	statment_delay(info); //coud be a double array to store delays as well as effect on carry
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
	if (init_info(core, &info, champ) == ERROR)
		return (ERROR);//free info and champ here before exiting
	if (game_start(core, info, champ) == ERROR)
		return (ERROR);//free info and champ here before exiting
	return (0);
}
