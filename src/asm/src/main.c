/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:16:33 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/18 10:20:22 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	validate_arguments(argc, argv);
	ft_printf("hello from asm %s\n", argv[1]);
	return (EXIT_SUCCESS);
}
