/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:32:55 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/18 12:13:10 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// t_input **create_buf(t_input **input, int size)
// {
// 	int	i;

// 	i = 0;
// 	if (size == -1)
// 	{
// 		ft_printf("Error: player position invalid\n");
// 		return (NULL);
// 	}
// 	input = (t_input **)malloc(size * sizeof(t_input *));
// 	if (!input)
// 		return (NULL);
// 	while (i < size)
// 	{
// 		input[i] = (t_input *)malloc(sizeof(t_input));
// 		if (!input[i])
// 		{
// 			error_clean(input, NULL, i + 1);
// 			return (NULL);
// 		}
// 		input[i]->champ_count = size;
// 		input[i]->filename = NULL;
// 		input[i]->t_script = (u_int8_t *) malloc (sizeof(u_int8_t) * (BUFF_SIZE * 2));
// 		if (!input[i]->t_script)
// 		{
// 			error_clean(input, NULL, i + 1);
// 			return (NULL);
// 		}
// 		input[i]->capacity = (BUFF_SIZE * 2);
// 		input[i]->current = 0;
// 		++i;
// 	}
// 	return (input);
// }

static int	store_buf(t_input *input, u_int8_t *buff, int size)
{
	int			i;
	u_int8_t	*temp;

	i = 0;
	temp = NULL;
	if (size == -1)
		return (-1);
	if (input->current + size >= input->capacity - 1)
	{
		temp = (u_int8_t *) malloc(sizeof(u_int8_t) * (input->capacity * 2));
		if (!temp)
			return (-1);
		ft_memcpy(temp, input->t_script, input->current);
		free(input->t_script);
		input->t_script = temp;
		input->capacity = input->capacity * 2;
	}
	while (i < size)
	{
		input->t_script[input->current] = buff[i];
		input->current++;
		++i;
	}
	return (0);
}

static int	read_binary(int fd, int ret, u_int8_t buff[BUFF_SIZE], t_input *input)
{
	ret = read(fd, buff, BUFF_SIZE);
	if (ret == -1)
	{
		ft_printf("Error: File %s is too small to be a champion\n", input->filename);
		return (ERROR);
	}
	while (ret)
	{
		if (store_buf(input, buff, ret) == -1)
			return (ERROR);
		ret = read(fd, buff, BUFF_SIZE);
	}
	return (0);
}

static int	open_binary(int *fd, int j, char *file, t_input *input)
{
	if (j != 0)
		close((*fd));
	(*fd) = open(file, O_RDONLY | 0);
	if ((*fd) == ERROR)
	{
		ft_printf("Can't read file %s\n", file);
		return (ERROR);
	}
	input->filename = ft_strdup(file);
	return (0);
}

t_input	**read_init(int argc, char **argv, int i, t_profile **champ)
{
	t_input		**input;
	u_int8_t	buff[BUFF_SIZE];
	int			fd;
	int			ret;
	int			pos[SIZE];

	input = NULL;
	input = create_buf(input, check_flag(i, argv, argc, &pos));
	if (!input)
		return (NULL);
	i = 0;
	ret = 0;
	while (i < input[0]->champ_count)
	{
		if (open_binary(&fd, i, argv[pos[i]], input[i]) == -1 || \
			read_binary(fd, ret, buff, input[i]) == -1)
		{
			error_clean(input, champ, input[0]->champ_count);
			return (NULL);
		}
		++i;
	}
	if (store_champs(champ, input[0]->champ_count, input) == -1)
		return (NULL);
	return (input);
}