/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:25:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/23 11:34:47 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexer_init(t_lexer *lexer)
{
	t_source	*source;

	lexer->next = NULL;
	source = &lexer->source;
	source_init(source);
	if (!source->buffer.alloc_size || !source->buffer.memory)
		exit_error_str(ERR_MSG_NO_SOURCE);
}

char	*lexer_buffer(t_lexer lexer)
{
	char	*str;

	str = (char *) lexer.source.buffer.memory;
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
		token++;
	return (token);
}

void	lexer_free(t_lexer *lexer)
{
	lexer->next = NULL;
	source_free(&lexer->source);
}
