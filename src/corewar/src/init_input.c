/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:13:26 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/20 11:52:26 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	Mallocing and error handle in case mallloc fails	*/
static int	mal_input(t_input **input, int i)
{
	input[i] = (t_input *)malloc(sizeof(t_input));
	if (!input[i])
	{
		error_clean(input, NULL, i + 1);
		return (ERROR);
	}
	return (0);
}

/*	Creating memory to store binary values read.
	Also initialising contents of structs	*/
t_input	**create_buf(t_input **input, int size)
{
	int	i;

	i = -1;
	if (size == -1)
	{
		ft_printf("HERE\n");
		return (NULL);
	}
	input = (t_input **)malloc(size * sizeof(t_input *));
	if (!input)
		return (NULL);
	while (++i < size)
	{
		if (mal_input(input, i))
			return (NULL);
		input[i]->champ_count = size;
		input[i]->filename = NULL;
		input[i]->t_script = (u_int8_t *) malloc \
			(sizeof(u_int8_t) * (BUFF_SIZE * 2));
		if (!input[i]->t_script)
		{
			error_clean(input, NULL, i + 1);
			return (NULL);
		}
		input[i]->capacity = (BUFF_SIZE * 2);
		input[i]->current = 0;
	}
	return (input);
}
