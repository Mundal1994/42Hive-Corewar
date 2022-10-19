/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:08:10 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/18 15:42:13 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Mallocing t_profile struct, as well as extending linked list		*/
static int	create_champ(t_profile	**champ)
{
	if (!(*champ))
	{
		(*champ) = (t_profile *) malloc (sizeof(t_profile));
		(*champ)->head = (*champ);
		if (!(*champ))
			return (-1);
		(*champ)->i = 1;
	}
	else
	{
		(*champ)->next = (t_profile *) malloc (sizeof(t_profile));
		if (!(*champ)->next)
			return (-1);
		(*champ)->next->head = (*champ)->head;
		(*champ)->next->i = (*champ)->i + 1;
		(*champ) = (*champ)->next;
	}
	(*champ)->exec_cd_sz = 0;
	(*champ)->next = NULL;
	return (0);
}

/*	Collection champions name	*/
static int	champ_name(t_profile **champ, t_input *input)
{
	int	j;
	int	k;

	j = 0;
	k = 4;
	while (j < PROG_NAME_LENGTH)
	{
		(*champ)->name[j] = input->t_script[k + j];
		++j;
	}
	k += j;
	while (k < 136)
	{
		if (input->t_script[k] != 0)
			return (-1);
		k++;
	}
	return (k);
}

/*	Collecting execution code size	*/
static int	champs_exec_cd(t_profile **champ, t_input *input, int *k)
{
	int	j;
	int	hold;

	j = 7;
	while ((*k) < 140)
	{
		hold = input->t_script[(*k)];
		(*champ)->exec_cd_sz += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		(*champ)->exec_cd_sz += (hold % 16) * ft_pow(16, j--);
		++(*k);
	}
	if ((*champ)->exec_cd_sz > MEM_SIZE / 6)
		return (ERROR);
	return (0);
}

/*	Checking execution code and its size, as well as comments	*/
static int	champ_stats(t_profile **champ, t_input **input, int i)
{
	int	j;
	int	k;

	k = champ_name(champ, input[i]);
	if (k == -1)
		return (k);
	if (champs_exec_cd(champ, input[i], &k) == -1)
		return (-1);
	j = 0;
	while (j < COMMENT_LENGTH)
	{
		(*champ)->comment[j] = input[i]->t_script[k + j];
		j++;
	}
	k += j;
	while (k < 2192)
	{
		if (input[i]->t_script[k] != 0)
			return (ERROR);
		k++;
	}
	return (0);
}

/*	Collecting champs name, comment and execution code, as well as error
	checking structure of file	*/
int	store_champs(t_profile **champ, int c, t_input **input)
{
	int	i;

	i = 0;
	while (i < c)
	{
		if (create_champ(champ) == -1)
			return (error_clean(input, champ, c));
		if (input[i]->t_script[0] != 0 || input[i]->t_script[1] \
			!= 234 || input[i]->t_script[2] != 131 || input[i]->t_script[3] \
			!= 243)
		{
			ft_printf("Error: File %s has an invalid header\n", \
				input[i]->filename);
			return (error_clean(input, champ, c));
		}
		ft_bzero((*champ)->name, (PROG_NAME_LENGTH + 1));
		ft_bzero((*champ)->comment, (COMMENT_LENGTH + 1));
		if (champ_stats(champ, input, i) == -1)
			return (error_clean(input, champ, c));
		++i;
	}
	(*champ) = (*champ)->head;
	return (0);
}
