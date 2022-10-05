/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:03:29 by cchen             #+#    #+#             */
/*   Updated: 2022/09/20 16:31:18 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	init_flag(t_info *info)
{
	int	i;

	i = 0;
	while (i < FLAG_COUNT)
	{
		info->flag[i] = FALSE;
		++i;
	}
}

static int	check_int_flag(char *str, t_info *info)
{
	if (!ft_strcmp(str, "-d"))
	{
		info->flag[D_FLAG] = TRUE;
		return (TRUE);
	}
	else if (!ft_strcmp(str, "-dc"))
	{
		info->flag[DC_FLAG] = TRUE;
		return (TRUE);
	}
	else if (!ft_strcmp(str, "-di"))
	{
		info->flag[DI_FLAG] = TRUE;
		return (TRUE);
	}
	else if (!ft_strcmp(str, "-c"))
	{
		info->flag[C_FLAG] = TRUE;
		return (TRUE);
	}
	else if (!ft_strcmp(str, "-s"))
	{
		info->flag[S_FLAG] = TRUE;
		return (TRUE);
	}
	else if (!ft_strcmp(str, "-v"))
	{
		info->flag[V_FLAG] = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static int	valid_flags(int argc, char **argv, t_info *info)
{
	init_flag(info);
	if (!ft_strcmp(argv[1], "-a"))
	{
		info->flag[A_FLAG] = TRUE;
		return (1);
	}
	else if (check_int_flag(argv[1], info))
	{
		if (argc > 3 && str_digit(argv[2]))
		{
			int i = 0;
			while (i < FLAG_COUNT)
			{
				if (info->flag[i])
					info->flag[i] = ft_atoi(argv[2]);
				++i;
			}
			return (2);//figure out how strict to be with this flag
		}
		else
			return (ERROR);
	}
	else if (!ft_strcmp(argv[1], "-i"))
	{
		info->flag[I_FLAG] = TRUE;
		return (1);
	}
	else if (!ft_strcmp(argv[1], "-vis"))
	{
		info->flag[I_FLAG] = TRUE;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;
	int		flag_count;

	if (argc > 1)
	{
		info = (t_info *)malloc(sizeof(t_info));
		if (!info)
			return (0);
		flag_count = valid_flags(argc, argv, info);
		if ((flag_count == 0 && argc <= 5 && argc >= 2) || \
			(flag_count == 1 && argc <= 6 && argc >= 3) || \
			(flag_count == 2 && argc <= 7 && argc >= 4))
		{
			if (init(argc, argv, flag_count + 1, info) == ERROR)
				return (ERROR);//depending on error either put USAGE MESSAGE or just exit completely and write error
		}
		else if (argc < 4 || flag_count == ERROR)
			return (ft_putendl(MSG_USAGE), 1);
		else
			return (ft_putendl(TOO_MANY_CHAMPS), 1);
	}
	else
		return (ft_putendl(MSG_USAGE), 1);
	return (0);
}

/*

testcase

./corewar -d 10000 champs/examples/bigzork.cor champs/examples/helltrain.cor
./corewar -d 100000 champs/examples/bigzork.cor champs/examples/helltrain.cor


Last print
./corewar -d 24366 champs/examples/bigzork.cor champs/examples/helltrain.cor
helltrain wins
./corewar -d 24367 champs/examples/bigzork.cor champs/examples/helltrain.cor

*/