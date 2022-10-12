/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:32:55 by jdavis            #+#    #+#             */
/*   Updated: 2022/10/12 16:14:29 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_input **create_buf(t_input **input, int argc, int c)
{
	int	i;

	i = 0;
	//if (!input)
	//{
		input = (t_input **)malloc((argc - c) * sizeof(t_input *));
		if (!input)
			return (NULL);
		while (i < (argc - c))
		{
			input[i] = (t_input *)malloc(sizeof(t_input));
			if (!input[i])
			{
				error_clean(input, NULL, i + 1);
				return (NULL);
			}
			//input[i]->t_script = NULL;
			input[i]->champ_count = c;
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
	//}
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
		return (-1);
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
			return (-1);
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
		return (ret);
	}
	while (ret)
	{
		if (store_buf(input, buff, ret) == -1)
		{
			//error_clean(input, NULL, (argc - input[j]->champ_count));
			return (-1);
		}
		ret = read(fd, buff, BUFF_SIZE);
	}
	return (0);
}

static int	open_binary(int *fd, int j, char *file, t_input *input)
{
	if (j != 0)
		close((*fd));
	(*fd) = open(file, O_RDONLY | 0);
	if ((*fd) == -1)
	{
		ft_printf("Can't read file %s\n", file);
		return (-1);
	}
	input->filename = ft_strdup(file);
	return (0);
}
static int	flag_check(int i, char **argv, int argc)
{
	int	j;
	int	count;
	int	champs[SIZE];
	int size;
	int	index;

	count = 0;
	size = 0;
	ft_bzero(champs, SIZE);
	while (i < argc - i)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			++i;
			j = 0;
			while (argv[i][j] != '\0')
			{
				if (!ft_isdigit(argv[i][j]))
					return (-1);
				++j;
			}
			//++i;
			if (ft_strstr(argv[i + 1], ".cor"))
			{
				index = ft_atoi(argv[i]);
				if (index > 4 || index < 1)
					return (-1);
				++count;
			}
		}
		++i;
	}
}
//static int	create_set(t_input **input, int *)
t_input	**read_init(int argc, char **argv, int i, t_profile **champ)
{
	t_input		**input;
	u_int8_t	buff[BUFF_SIZE];
	int			fd;
	int			ret;
	int			j;

	input = NULL;
	input = create_buf(input, argc, i);
	if (!input)
		return (NULL);
	j = 0;
	ret = 0;
	while (i < argc)
	{
		if (open_binary(&fd, j, argv[i],input[j]) == -1 || \
			read_binary(fd, ret, buff, input[j]) == -1)
		{
			error_clean(input, champ, (argc - input[j]->champ_count));
			return (NULL);
		}
		++j;
		++i;
	}
	if (store_champs(champ, argc - input[0]->champ_count, input) == -1)
		//free(info) outside!!!
		return (NULL);
	return (input);
}