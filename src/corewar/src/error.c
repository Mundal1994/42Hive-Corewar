/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:34:08 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/19 15:47:02 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Freeing last element of champs struct	*/
static int	error_final_head(t_profile **champ)
{
	if ((*champ) == (*champ)->head)
	{
		free((*champ)->head);
		(*champ) = NULL;
		return (1);
	}
	return (0);
}

/*	Freeing input array of type pointer to t_input struct	*/
static void	free_input(t_input **input, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		if (input[i]->filename)
			free(input[i]->filename);
		if (input[i]->t_script)
			free(input[i]->t_script);
		input[i]->filename = NULL;
		input[i]->t_script = NULL;
		if (input[i])
			free(input[i]);
		++i;
	}
	free(input);
	input = NULL;
}

/*	freeing champs linked list	*/
int	error_clean(t_input **input, t_profile **champ, int c)
{
	t_profile	*temp;

	if (champ)
	{
		while ((*champ) && (*champ)->head)
		{
			if (error_final_head(champ))
				break ;
			temp = (*champ)->head;
			(*champ)->head = (*champ)->head->next;
			free(temp);
		}
	}
	if (input)
		free_input(input, c);
	return (-1);
}

/*	Printing error messages and returning ERROR	*/
int	error_print(char *str)
{
	ft_printf("%s\n", str);
	return (ERROR);
}
