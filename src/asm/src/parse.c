/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:45:41 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 21:08:57 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_init(t_ast *ast, t_lexer *lexer)
{
	lexer->next = NULL;
	if (ast_init(ast) == OK)
		return ;
	vec_free(&lexer->buffer);
	exit_error_str(ERR_MSG_AST_INIT_FAIL);
}

void	parse(t_ast *ast, t_lexer *lexer)
{
	parse_init(ast, lexer);
	parse_header(&ast->header, lexer);
}
