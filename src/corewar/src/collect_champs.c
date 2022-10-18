/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_champs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:55:08 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/18 12:02:09 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	collect_players(char **argv, int *i, int (*pos)[SIZE], int *max_ind)
{
	int	j;
	int	index;

	j = 0;
	++(*i);
	while (argv[(*i)][j] != '\0')
	{
		if (!ft_isdigit(argv[(*i)][j]))
			return (ERROR);
		++j;
	}
	if (ft_strstr(argv[(*i) + 1], ".cor"))
	{
		index = ft_atoi(argv[(*i)]);
		if (index > 4 || index < 1 || (*pos)[index - 1])
		{
			return (ERROR);
		}
		if ((*max_ind) < index)
			(*max_ind) = index;
		(*pos)[index - 1] = ++(*i);
	}
	else
		return (ERROR);
	return ((*max_ind));
}

static int	range_invalid(int max_ind, int pos[SIZE], int *j)
{
	int i;

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
				return (ERROR);
			if (!(*pos)[j])
			{
				(*pos)[j++] = (*champs)[i];
				break ;
			}
			++j;
		}
		++i;
	}
	//ft_printf("%i < %i   %i > %i   %i \n", i, size, max_ind, j, range_invalid(max_ind, (*pos), &j));
	if (i < size || range_invalid(max_ind, (*pos), &j) || (size != 0 && max_ind > j) )
		return (ERROR);
	return (j);
}

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

int	check_flag(int i, char **argv, int argc, int (*pos)[SIZE])
{
	int	champs[SIZE];
	int size;
	int max_ind;

	size = 0;
	max_ind = 0;
	initialise_arr(&champs, pos);
	while (i < argc)
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
				return (ERROR);
			champs[size++] = i;
		}
		else
			return (ERROR);
		++i;
	}
	return (combine_players(size, max_ind, &champs, pos));
}
