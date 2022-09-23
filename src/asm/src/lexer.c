/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:25:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/23 17:04:54 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexer_init(t_lexer *lexer)
{
	t_vec	*buffer;

	lexer->next = NULL;
	buffer = &lexer->source.buffer;
	if (!buffer->alloc_size || !buffer->memory)
		exit_error_str(ERR_MSG_NO_SOURCE);
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
