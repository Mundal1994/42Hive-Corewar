#include "../vm_champs/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

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
	//ft_printf("current %i\n", input->current);
	while (i < size)
	{
		input->t_script[input->current] = buff[i];
		//ft_printf("%c", buff[i]);//input->t_script[input->current]);
		input->current++;
		++i;
	}
	//ft_printf("size %i\n", input->current);
	// if (input->current > 682) //MEM_SIZE / 6
	// {
	// 	ft_printf("HERE LIES\n");
	// 	return (-1);
	// }
	//ft_printf("\n");
	return (0);
}

static int	usage_champs_count(int argc)
{
	if (argc == 1 || argc > 5)
	{
		if (argc > 5)
			ft_printf("Too many champions\n");
		else
		//if (argc == 1)
			ft_printf("Usage: ./corewar [-d N -s N -v N \
			| -b --stealth | -n --stealth] [-a] <champion1.cor> \
			<...>\n    -a        : Prints output from \"aff\" \
			(Default is to hide it)\n#### TEXT OUTPUT MODE \
			##########################################################\n \
			-d N      : Dumps memory after N cycles then exits\n    -s N \
					: Runs N cycles, dumps memory, pauses, then repeats\n    \
			-v N      : Verbosity levels, can be added together to enable \
			several\n                - 0 : Show only essentials\n  \
						- 1 : Show lives\n               \
			- 2 : Show cycles\n                - 4 : \
			Show operations (Params are NOT litteral ...)\n \
							- 8 : Show deaths\n                \
			- 16 : Show PC movements (Except \
			for jumps)\n#### BINARY OUTPUT MODE \
			########################################################\n    \
			-b        : Binary output mode for corewar.42.fr\n    --stealth \
			: Hides the real contents of the memory\n#### NCURSES OUTPUT MODE \
			#######################################################\n    -n    \
				: Ncurses output mode\n    --stealth : Hides the real contents of \
				the memory\n################################################################################");
		return (-1);
	}
	return (0);
}

static t_profile **store_champs(t_profile **champ, int argc, t_input **input)
{
	int i;
	int	j;
	int	k;

	i = 0;
	if (!champ)
	{
		champ = (t_profile **) malloc ((argc - 1) * sizeof(t_profile));
		if (!champ)
		{
			//free everything
			return (NULL);
		}
		while (i < (argc - 1))
		{
			if (input[i]->t_script[0] != 0 || input[i]->t_script[1] \
				!= 234 || input[i]->t_script[2] != 131 || input[i]->t_script[3] \
				!= 243)
				exit (1);
			champ[i] = (t_profile *) malloc (sizeof(t_profile));
			if (!champ[i])
			{
				//free all 
				return (NULL);
			}
			ft_bzero(champ[i]->name, 129); //(PROG_NAME_LENGTH + 1)
			ft_bzero(champ[i]->comment, 2049); //(COMMENT_LENGTH + 1)what checks unprintable chars?
			j = 0;
			k = 4;
			while (j < 128) //PROG_NAME_LENGTH
			{
				champ[i]->name[j] = input[i]->t_script[k + j];
				++j;
			}
			k += j;
			//ft_printf("%i\n", k);
			//exit (0);
			while (k < 136)
			{
				if (input[i]->t_script[k] != 0)
				{
					ft_printf("PROBLEM\n");
					//if next four bytes arent NULL
					exit (1);
				}
				k++;
			}
			//ft_printf("%i\n", k);
			//exit (0);
			champ[i]->exec_cd_sz = 0;
			while (k < 140)
			{
				champ[i]->exec_cd_sz += input[i]->t_script[k];
				++k;
			}
			//ft_printf("exec %i\n", champ[i]->exec_cd_sz);
			//exit (0);
			j = 0;
			while (j < 2048)
			{
				champ[i]->comment[j] = input[i]->t_script[k + j];
				j++;
			}
			k += j;
			while (k < 2192)
			{
				if (input[i]->t_script[k] != 0)
				{
					ft_printf("PROBLEM\n");
					//if next four bytes arent NULL
					exit (1);
				}
				k++;
			}
			++i;
		}
	}
	return (champ);
}

int	main (int argc, char *argv[])
{
	int			fd;
	t_input		**input;
	int			ret;
	u_int8_t	buff[BUFF_SIZE];
	size_t		i;
	t_profile	**champ;

	i = 1;
	input = NULL;
	if (usage_champs_count(argc) == -1)
		return (-1);
	input = create_buf(input, argc);
	if (!input)
	{
		return (-1);
	}
	while ((int)i < argc)
	{
		//file passed ends with .cor
		//add check got max size of file
		fd = open(argv[i], O_RDONLY | 0);
		if (fd == -1)
		{
			ft_printf("Can't read file %s\n", argv[i]);
			return (-1);
		}
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
		{
			//clean out
			return (-1);
		}
		while (ret)
		{
			if (store_buf(input[i - 1], buff, ret) == -1)
			{
				//free(input[i]->t_script); all
				//free(input[i]); all
				//free(input);
				return (-1);
			}
			ret = read(fd, buff, BUFF_SIZE);
		}
		//collect and store information
		++i;
	}
	champ = NULL;
	champ = store_champs(champ, argc, input);
	// i = 0;
	// while (i < input->current)
	// {
	// 	if ((input->t_script[i] >= 'a' && input->t_script[i] <= 'z') || (input->t_script[i] >= 'A' && input->t_script[i] <= 'Z'))
	// 		ft_printf("%c", input->t_script[i]);
	// 	i++;
	// }

	return (0);
}