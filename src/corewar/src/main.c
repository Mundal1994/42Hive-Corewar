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

static int	valid_flags(int argc, char **argv)
{
	if (!ft_strcmp(argv[1], "-d") || !ft_strcmp(argv[1], "-s") || \
		!ft_strcmp(argv[1], "-v"))
	{
		if (argc > 3 && str_digit(argv[2]))
			return (2);//figure out how strict to be with this flag
		else
			return (ERROR);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	flag_count;

	flag_count = valid_flags(argc, argv);
	if ((flag_count == 0 && argc <= 5 && argc >= 2) || \
		(flag_count == 1 && argc <= 6 && argc >= 3) || \
		(flag_count == 2 && argc <= 7 && argc >= 4))
	{
		init(argc, argv, flag_count + 1);
	}
	else if (argc < 4 || flag_count == ERROR)
		return (ft_putendl(MSG_USAGE), 1);
	else
		return (ft_putendl(TOO_MANY_CHAMPS), 1);
	return (0);
}
