/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:40:01 by cchen             #+#    #+#             */
/*   Updated: 2022/09/20 14:40:02 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	node_make(t_node *node, char *token, uint8_t type)
{
	if (!node)
		return (error(ERR_MSG_NO_NODE));
	if (!token)
		return (error(ERR_MSG_NO_TOKEN));
	if (type > ARGUMENT)
		return (error(ERR_MSG_BAD_TYPE));
	node->type = type;
	node->token = token;
	if (type == LABEL || type == STATEMENT)
		return (vec_new(&node->nodes, 1, sizeof(node->nodes)));
	ft_bzero(&node->nodes, sizeof(node->nodes));
}

int	node_push(t_node *dst, t_node *src)
{
	if (!dst || !src)
		return (error(ERR_MSG_NO_NODE));
	if (src->type == LABEL || src->type == STATEMENT)
	{
		if (dst->type != LABEL)
			return (error(ERR_MSG_BAD_ORDER));
		if (dst->nodes.len == 0)
			return (vec_push(&dst->nodes, src));
	}
	if (src->type == ARGUMENT)
	{
		if (dst->type == ARGUMENT)
			return (error(ERR_MSG_BAD_ORDER));
		if (dst->type == STATEMENT)
			return (vec_push(&dst->nodes, src));
	}
	return (node_push(node_get(dst, 0), src));
}

t_node	*node_get()


void	node_free(t_node *node)
{
	if (node->nodes.memory == NULL)
	{
		vec_free(node);
	}
}
