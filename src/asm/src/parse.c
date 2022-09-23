/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:45:41 by cchen             #+#    #+#             */
/*   Updated: 2022/09/23 17:05:25 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_init(t_ast *ast, t_lexer *lexer)
{
	lexer_init(lexer);
	if (ast_init(ast) == OK)
		return ;
	lexer_free(lexer);
	exit_error_str(ERR_MSG_AST_INIT_FAIL);
}

void	parse(t_ast *ast, t_lexer *lexer)
{
	parse_init(ast, lexer);
}
