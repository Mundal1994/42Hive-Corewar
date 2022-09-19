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

typedef enum e_type
{
	LABEL,
	STATEMENT,
	ARGUMENT
}		t_type;

typedef struct s_node
{
	uint8_t	type;
	char	*token;
	t_vec	nodes;
}		t_node;

/* Abstract Syntax Tree */
typedef struct s_ast
{
	t_vec	nodes;
}		t_ast;

#endif
