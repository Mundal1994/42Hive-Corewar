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

static void	parse_init(t_ast *ast, t_vec *buffer)
{
	if (ast_init(ast) == OK)
		return ;
	vec_free(buffer);
	error(ERR_MSG_AST_INIT_FAIL);
	exit(EXIT_FAILURE);
}

void	parse(t_ast *ast, t_lexer *lexer)
{
	lexer->next = NULL;
	parse_init(ast, &lexer->buffer);
	parse_header(&ast->header, lexer);
}
