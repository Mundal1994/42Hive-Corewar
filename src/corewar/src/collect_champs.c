/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_champs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:55:08 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/20 11:52:40 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	collects players according to arguments specified using 
	the -n flag
*/
static int	collect_players(char **argv, int *i, int (*pos)[SIZE], int *max_ind)
{
	int	j;
	int	index;

	j = 0;
	++(*i);
	while (argv[(*i)][j] != '\0')
	{
		if (!ft_isdigit(argv[(*i)][j]))
			return (error_print("Error: invalid position"));
		++j;
	}
	if (ft_strstr(argv[(*i) + 1], ".cor"))
	{
		index = ft_atoi(argv[(*i)]);
		if (index > 4 || index < 1 || (*pos)[index - 1])
			return (error_print("Error: invalid position"));
		if ((*max_ind) < index)
			(*max_ind) = index;
		(*pos)[index - 1] = ++(*i);
	}
	else
		return (error_print("Error: invalid file"));
	return ((*max_ind));
}

/*	checks players have been placed without gaps inbetween */
static int	range_invalid(int max_ind, int pos[SIZE], int *j)
{
	int	i;

	i = 0;
	while (i < max_ind)
	{
		if (pos[i] == 0)
			(*j) = -1;
		++i;
	}
	i = max_ind;
	while (i < SIZE)
	{
		if (pos[i])
			++max_ind;
		else
			break ;
		++i;
	}
	if ((*j != -1))
		(*j) = max_ind;
	return (0);
}

/*	combines players collected on the different arrays, to see if
	players are placed in invalid postions
*/
static int	combine_players(int size, int max_ind, int (*champs)[SIZE], \
	int (*pos)[SIZE])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while ((*champs)[i])
		{
			if (j >= SIZE)
				return (error_print("Too many chapions"));
			if (!(*pos)[j])
			{
				(*pos)[j++] = (*champs)[i];
				break ;
			}
			++j;
		}
		++i;
	}
	if (i < size || range_invalid(max_ind, (*pos), &j) \
		|| (size != 0 && max_ind > j) || j == -1)
		return (error_print("Error: invalid position"));
	return (j);
}

/*	initialises arrays used to collect player positions*/
static	void	initialise_arr(int (*champs)[SIZE], int (*pos)[SIZE])
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		(*champs)[i] = 0;
		(*pos)[i++] = 0;
	}
}

/*	checking if players have been placed using -n flag or
	not. Plus errors with placement
*/
int	check_flag(int i, char **argv, int argc, int (*pos)[SIZE])
{
	int	champs[SIZE];
	int	size;
	int	max_ind;

	size = 0;
	max_ind = 0;
	initialise_arr(&champs, pos);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-n") && i + 2 < argc)
		{
			max_ind = collect_players(argv, &i, pos, &max_ind);
			if (max_ind == ERROR)
				return (ERROR);
		}
		else if (ft_strstr(argv[i], ".cor"))
		{
			if (size > 3)
				return (error_print("Too many champions"));
			champs[size++] = i;
		}
		else
			return (error_print("Error: invalid argument"));
	}
	return (combine_players(size, max_ind, &champs, pos));
}
