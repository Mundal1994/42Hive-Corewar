/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:33:43 by cchen             #+#    #+#             */
/*   Updated: 2022/09/20 14:33:45 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* Initializes Abstract Syntax Tree data */
int	ast_init(t_ast *ast)
{
	t_header	*header;

	header = ast->header;
	header->magic = COREWAR_EXEC_MAGIC;
	header->prog_size = 0;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	if (vec_new(&ast->statements, 1, sizeof(t_statement)) == OK
		&& hashmap_new(&ast->labels) == OK)
		return (OK);
	ast_free(&ast);
	return (perror(ERR_MSG_AST_INIT_FAIL), ERROR);
}

void	ast_free(t_ast **ast)
{
	if ((*ast)->statements.memory)
		vec_free(&(*ast)->statements);
	hashmap_free(&(*ast)->labels);
	*ast = NULL;
}
