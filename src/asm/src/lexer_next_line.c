/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:11:39 by cchen             #+#    #+#             */
/*   Updated: 2022/09/22 17:11:40 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_empty_line(char *token)
{
	while (*token && ft_strchr(TABSPACE, *token))
		++token;
	return (*token == '\0' || ft_strchr("#;", *token));
}

char	*lexer_next_line(t_lexer *lexer)
{
	char	*token;

	token = lexer_next(lexer, NEWLINE);
	while (is_empty_line(token))
		token = lexer_next(lexer, NEWLINE);
	return (token);
}
