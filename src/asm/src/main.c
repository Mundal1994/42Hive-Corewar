/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:16:33 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/26 10:54:01 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "validator.h"
#include "assemble.h"

int	main(int argc, char **argv)
{
	t_parser	parser;

	validate_arguments(argc, argv);
	parse(&parser, argv[1]);
	assemble(&parser, argv[1]);
	return (EXIT_SUCCESS);
}
