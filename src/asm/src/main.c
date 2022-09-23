/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:16:33 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/23 17:01:02 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_lexer		lexer;
	t_ast		ast;

	validate_arguments(argc, argv);
	source_init(&lexer.source);
	source_read(&lexer.source, argv[1]);
	parse(&ast, &lexer);
	ast_free(&ast);
	lexer_free(&lexer);
	return (EXIT_SUCCESS);
}
