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
	t_lexer	lexer;
	t_ast	ast;

	validate_arguments(argc, argv);
	io_read(argv[1], &lexer.buffer);
	parse(&ast, &lexer);
	vec_free(&lexer.buffer);
	return (EXIT_SUCCESS);
}
