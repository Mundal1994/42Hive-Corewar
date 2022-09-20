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
	/*	added non useful comment to test pull requests	*/
	if (argc < 2)
		return (ft_putendl(MSG_USAGE), 1);
	ft_putendl(argv[0]);
	return (0);
}
