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

#include "asm.h"

int	main(int argc, char **argv)
{
	t_lexer		lexer;

	validate_arguments(argc, argv);
	lexer_init(&lexer, argv[1]);
	assemble(&lexer);
	lexer_free(&lexer);
	return (EXIT_SUCCESS);
}
