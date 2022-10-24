/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:03:29 by cchen             #+#    #+#             */
/*   Updated: 2022/10/13 11:26:10 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*	frees info and puts usage message	*/
static int	free_and_return(t_info **info)
{
	free(*info);
	return (ft_putendl(MSG_USAGE), 1);
}

/*
checks argc and makes sure the minimum requirements are meet before
calling the init function
*/
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
			(flag_count == 2 && argc >= 4))
		{
			init(argc, argv, flag_count + 1, info);
			free(info);
		}
		else
			return (free_and_return(&info));
	}
	else
		return (ft_putendl(MSG_USAGE), 1);
	return (0);
}
