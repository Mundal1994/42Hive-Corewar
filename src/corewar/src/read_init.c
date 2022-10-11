#include "vm.h"

t_input **create_buf(t_input **input, int argc, int c)
{
	int	i;

	i = 0;
	if (!input)
	{
		//ft_printf("plus %d\n", argc - c);
		input = (t_input **)malloc((argc - c) * sizeof(t_input *));
		if (!input)
		{
			return (NULL);
		}
		while (i < (argc - c))
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
	if (input->current + size >= input->capacity - 1)
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
	int	hold;

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
	j = 7;
	while (k < 140)
	{
		hold = input[i]->t_script[k];
		(*champ)->exec_cd_sz += (hold / 16) * ft_pow(16, j--);
		hold %= 16;
		(*champ)->exec_cd_sz += (hold % 16) * ft_pow(16, j--);
		//might need to be in a while loop till hold % 16 is 0
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
int	error_clean(t_input **input, t_profile **champ, int c)
{
	t_profile	*temp;
	int			i;

	i = 0;
	while ((*champ) && (*champ)->head)
	{
		if (error_final_head(champ))
			break ;
		temp = (*champ)->head;
		(*champ)->head = (*champ)->head->next;
		free(temp);
	}
	if (input)
	{
		while (i < c)
		{
			free(input[i]->filename);
			free(input[i]->t_script);
			free(input[i]);
			++i;
		}
		free(input);
		input = NULL;
	}
	return (-1);
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

t_input	**read_init(int argc, char **argv, int i, t_profile **champ)
{
	t_input		**input;
	u_int8_t	buff[BUFF_SIZE];
	int			fd;
	int			ret;
	int			origin_i;
	int			j;

	input = NULL;
	input = create_buf(input, argc, i);
	if (!input)
		return (NULL);
	origin_i = i;
	j = 0;
	while (i < argc)
	{
		//add check got max size of file
		if (j != 0)
			close(fd);
		fd = open(argv[i], O_RDONLY | 0);
		if (fd == -1)
		{
			ft_printf("Can't read file %s\n", argv[i]);
			error_clean(input, champ, (argc - origin_i));
			return (NULL);
		}
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
		{
			error_clean(input, champ, (argc - origin_i));
			return (NULL);
		}
		input[j]->filename = ft_strdup(argv[i]);
		while (ret)
		{
			if (store_buf(input[j], buff, ret) == -1)
				return (NULL);
			ret = read(fd, buff, BUFF_SIZE);
		}
		++j;
		++i;
	}
	if (store_champs(champ, argc - origin_i, input) == -1)
		//free(info) outside!!!
		return (NULL);
	return (input);
}