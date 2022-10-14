/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:32:55 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/14 13:59:07 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_input **create_buf(t_input **input, int size)
{
	int	i;

	i = 0;
	if (size == -1)
	{
		ft_printf("Error: player position invalid\n");
		return (NULL);
	}
	input = (t_input **)malloc(size * sizeof(t_input *));
	if (!input)
		return (NULL);
	while (i < size)
	{
		input[i] = (t_input *)malloc(sizeof(t_input));
		if (!input[i])
		{
			error_clean(input, NULL, i + 1);
			return (NULL);
		}
		//input[i]->t_script = NULL;
		input[i]->champ_count = size;
		input[i]->filename = NULL;
		input[i]->t_script = (u_int8_t *) malloc (sizeof(u_int8_t) * (BUFF_SIZE * 2));
		if (!input[i]->t_script)
		{
			//free_2d() along with input[i]->t_script
			//free(input);
			error_clean(input, NULL, i + 1);
			return (NULL);
		}
		input[i]->capacity = (BUFF_SIZE * 2);
		input[i]->current = 0;
		++i;
	}
	return (input);
}

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

static int	create_champ(t_profile	**champ)
{
	if (!(*champ))
	{
		(*champ) = (t_profile *) malloc (sizeof(t_profile));
		(*champ)->head = (*champ);
		if (!(*champ))
		{
			//free everything
			return (-1);
		}
		(*champ)->i = 1;
	}
	else
	{
		(*champ)->next = (t_profile *) malloc (sizeof(t_profile));
		if (!(*champ)->next)
		{
			//free head
			return (-1);
		}
		(*champ)->next->head = (*champ)->head;
		(*champ)->next->i = (*champ)->i + 1;
		(*champ) = (*champ)->next;
	}
	(*champ)->exec_cd_sz = 0;
	(*champ)->next = NULL;
	return (0);
}

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
static int	champs_exec_cd(t_profile **champ, t_input *input, int *k)
{
	int	j;
	int hold;

	j = 7;
	while ((*k) < 140)
	{
		hold = input->t_script[(*k)];
		(*champ)->exec_cd_sz += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		(*champ)->exec_cd_sz += (hold % 16) * ft_pow(16, j--);
		//might need to be in a while loop till hold % 16 is 0
		++(*k);
	}
	if ((*champ)->exec_cd_sz > MEM_SIZE / 6)
		return (ERROR);
	return (0);
}

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

static int	store_champs(t_profile **champ, int c, t_input **input)
{
	int i;

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
		{
			//error_clean(input, NULL, (argc - input[j]->champ_count));
			return (ERROR);
		}
		ret = read(fd, buff, BUFF_SIZE);
	}
	return (0);
}

static int	open_binary(int *fd, int j, char *file, t_input *input)
{
	if (j != 0)
		close((*fd));//better way to close with 
	(*fd) = open(file, O_RDONLY | 0);
	if ((*fd) == ERROR)
	{
		ft_printf("Can't read file %s\n", file);
		return (ERROR);
	}
	input->filename = ft_strdup(file);
	return (0);
}

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
			return (ERROR);
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
			//return (ERROR);
		++i;
	}
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
		if ((*champs)[i])
		{
			while (j < SIZE && (*pos)[j])
				++j;
			(*pos)[j++] = (*champs)[i];
			while (j < SIZE && (*pos)[j])
				++j;
		}
		++i;
		if (j >= SIZE)
			break ;
	}
	if (i < size || (size != 0 && max_ind > j) || range_invalid(max_ind, (*pos), &j))
	{
		//ft_printf("Error: player not within range\n");
		return (ERROR);
	}
	return (j);
}

static int	flag_check(int i, char **argv, int argc, int (*pos)[SIZE])
{
	int	j;
	int	champs[SIZE];
	int size;
	int max_ind;

	size = 0;
	j = 0;
	max_ind = 0;
	while (j < SIZE)
	{
		champs[j] = 0;
		(*pos)[j++] = 0;
	}
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-n") && i + 2 < argc)
		{
			max_ind = collect_players(argv, &i, pos, &max_ind);
			if (max_ind == ERROR)
			{
				//ft_printf("CHECK\n");
				//ft_printf("Error: player position invalid\n");
				return (ERROR);
			}
		}
		else if (ft_strstr(argv[i], ".cor"))
		{
			if (size > 3)
				return (ERROR);
			champs[size++] = i;
		}
		else
		{
			return (ERROR);
		}
		++i;
	}
	return (combine_players(size, max_ind, &champs, pos));
}

t_input	**read_init(int argc, char **argv, int i, t_profile **champ)
{
	t_input		**input;
	u_int8_t	buff[BUFF_SIZE];
	int			fd;
	int			ret;
	int			pos[SIZE];

	input = NULL;
	input = create_buf(input, flag_check(i, argv, argc, &pos));
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
		//++j;
		++i;
	}
	if (store_champs(champ, input[0]->champ_count, input) == -1)
		//free(info) outside!!!
		return (NULL);
	return (input);
}