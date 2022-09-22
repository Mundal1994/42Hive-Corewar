/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:25:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 14:26:44 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexer_init(t_lexer *lexer)
{
	lexer->next = NULL;
	lexer->row = 1;
}

char	*lexer_buffer(t_lexer lexer)
{
	char	*str;

	str = (char *) lexer.buffer.memory;
	return (str);
}

char	*lexer_next(t_lexer *lexer, const char *delim)
{
	char	*buffer;

	buffer = NULL;
	if (lexer->next == NULL)
		buffer = lexer_buffer(*lexer);
	return (ft_strtok_r(buffer, delim, &lexer->next));
}

char	*lexer_token_trim_start(t_lexer *lexer, char *token)
{
	if (!lexer || !token)
		return (NULL);
	while (*token && ft_strchr(WHITESPACE, *token))
		lexer->row += *token++ == '\n';
	return (token);
}

void	lexer_free(t_lexer *lexer)
{
	if (lexer->buffer.memory)
		vec_free(&lexer->buffer);
	lexer->next = NULL;
}
