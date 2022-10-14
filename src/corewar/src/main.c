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


int	main(int argc, char **argv)
{
	t_info	*info;
	int		flag_count;

	if (argc > 1)
	{
		info = (t_info *)malloc(sizeof(t_info));
		if (!info)
			return (0);
		flag_count = init_flags(argc, argv, info);
		if ((flag_count == 0 && argc >= 2) || \
			(flag_count == 1 && argc >= 3) || \
			(flag_count == 2 && argc >= 4))//removed  && argc <= 5		&& argc <= 6		&& argc <= 7
		{
			if (init(argc, argv, flag_count + 1, info) == ERROR)
			{
				free(info);
				return (ERROR);//depending on error either put USAGE MESSAGE or just exit completely and write error
			}
			//print this error message if too many champs
			//return (ft_putendl(TOO_MANY_CHAMPS), 1);
		}
		else
		{
			free(info);
			if (flag_count == ERROR)
				ft_printf("Error: flags can't be combined with minus number\n\n");
			return (ft_putendl(MSG_USAGE), 1);
		}
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