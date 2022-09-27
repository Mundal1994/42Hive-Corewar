#include "vm.h"

t_input **create_buf(t_input **input, int argc)
{
	int	i;

	i = 0;
	if (!input)
	{
		input = (t_input **)malloc((argc - 1) * sizeof(t_input *));
		if (!input)
		{
			return (NULL);
		}
		while (i < (argc - 1))
		{
			input[i] = (t_input *)malloc(sizeof(t_input));
			if (!input[i])
			{
				//free_2d() along with input[i]->t_script
				return (NULL);
			}
			input[i]->t_script = (u_int8_t *) malloc (sizeof(u_int8_t) * (BUFF_SIZE * 2));
			if (!input[i]->t_script)
			{
				//free_2d() along with input[i]->t_script
				//free(input);
				return (NULL);
			}
			input[i]->capacity = (BUFF_SIZE * 2);
			input[i]->current = 0;
			++i;
		}
	}
	return (input);
}

static int	store_buf(t_input *input, u_int8_t *buff, size_t size)
{
	size_t			i;
	u_int8_t	*temp;

	i = 0;
	temp = NULL;
	if (input->current + size >= input->capacity)
	{
		temp = (u_int8_t *) malloc(sizeof(u_int8_t) * (input->capacity * 2));
		if (!temp)
		{
			return (-1);
		}
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

static int	champ_stats(t_profile **champ, t_input **input, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 4;
	while (j < PROG_NAME_LENGTH)
	{
		(*champ)->name[j] = input[i]->t_script[k + j];
		++j;
	}
	k += j;
	while (k < 136)
	{
		if (input[i]->t_script[k] != 0)
			return (-1);
		k++;
	}
	while (k < 140)
	{
		(*champ)->exec_cd_sz += input[i]->t_script[k];
		++k;
	}
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

int	error_clean(t_input **input, t_profile **champ, int c)
{
	t_profile	*temp;
	int			i;

	i = 0;
	while ((*champ) && (*champ)->head)
	{
		if ((*champ) == (*champ)->head)
			(*champ) = NULL;
		temp = (*champ)->head;
		(*champ)->head = (*champ)->head->next;
		free(temp);
	}
	if (input)
	{
		while (i < c)
		{
			free(input[i]->t_script);
			free(input[i]);
			++i;
		}
		free(input);
		input = NULL;
	}
	return (-1);
}

static int	store_champs(t_profile **champ, int argc, t_input **input, int c)
{
	int i;
	//int	j;
	//int	k;

	i = 0;
	while (i < (argc - c))
	{
		if (create_champ(champ) == -1)
			return (error_clean(input, champ, c));
		if (input[i]->t_script[0] != 0 || input[i]->t_script[1] \
			!= 234 || input[i]->t_script[2] != 131 || input[i]->t_script[3] \
			!= 243)
		{
			exit (1);
		}
		ft_bzero((*champ)->name, (PROG_NAME_LENGTH + 1)); //(PROG_NAME_LENGTH + 1)
		ft_bzero((*champ)->comment, (COMMENT_LENGTH + 1)); //(COMMENT_LENGTH + 1)what checks unprintable chars?
		if (champ_stats(champ, input, i) == -1)
			return (error_clean(input, champ, c));
		// j = 0;
		// k = 4;
		// while (j < PROG_NAME_LENGTH)
		// {
		// 	(*champ)->name[j] = input[i]->t_script[k + j];
		// 	++j;
		// }
		// k += j;
		// while (k < 136)
		// {
		// 	if (input[i]->t_script[k] != 0)
		// 	{
		// 		ft_printf("PROBLEM\n");
		// 		//if next four bytes arent NULL
		// 		exit (1);
		// 	}
		// 	k++;
		// }
		// while (k < 140)
		// {
		// 	(*champ)->exec_cd_sz += input[i]->t_script[k];
		// 	++k;
		// }
		// j = 0;
		// while (j < COMMENT_LENGTH)
		// {
		// 	(*champ)->comment[j] = input[i]->t_script[k + j];
		// 	j++;
		// }
		// k += j;
		// while (k < 2192)
		// {
		// 	if (input[i]->t_script[k] != 0)
		// 	{
		// 		ft_printf("PROBLEM\n");
		// 		//if next four bytes arent NULL
		// 		exit (1);
		// 	}
		// 	k++;
		// }
		++i;
	}
	(*champ) = (*champ)->head;
	return (0);
}

t_input	**read_init(int argc, char **argv, int i, t_profile **champ)
{
	t_input		**input;
	u_int8_t	buff[BUFF_SIZE];
	int			fd;
	int			ret;
	int			origin_i;
	int			j;

	input = NULL;
	input = create_buf(input, argc);
	if (!input)
	{
		return (NULL);
	}
	origin_i = i;
	j = 0;
	while (i < argc)
	{
		//file passed ends with .cor
		//add check got max size of file
		if (j != 0)
			close(fd);
		fd = open(argv[i], O_RDONLY | 0);
		if (fd == -1)
		{
			ft_printf("Can't read file %s\n", argv[i]);
			return (NULL);
		}
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
		{
			//clean out
			return (NULL);
		}
		while (ret)
		{
			if (store_buf(input[j], buff, ret) == -1)
			{
				//free(input[i]->t_script); all
				//free(input[i]); all
				//free(input);
				return (NULL);
			}
			ret = read(fd, buff, BUFF_SIZE);
		}
		//collect and store information
		++j;
		++i;
	}
	if (store_champs(champ, argc, input, origin_i) == -1)//PROBLEM
		return (NULL);
	// while ((*champ))
	// {
	// 	ft_printf("i: %d\n", (*champ)->i);
	// 	ft_printf("name: %s\n", (*champ)->name);
	// 	ft_printf("comment: %s\n", (*champ)->comment);
	// 	ft_printf("exec code: %d\n", (*champ)->exec_cd_sz);
	// 	(*champ) = (*champ)->next;
	// }
	return (input);
}