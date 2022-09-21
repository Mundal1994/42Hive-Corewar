/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:48:21 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/19 11:23:24 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_statement
{
	t_op	operation;
	t_vec	args;
}				t_statement;

/* Abstract Syntax Tree */
typedef struct s_ast
{
	t_header	header;
	t_vec		statements;
	t_hashmap	labels;
}		t_ast;

void	ast_init(t_ast *ast);
#endif
