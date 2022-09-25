/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:25:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/25 11:23:48 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexer(t_lexer *lexer)
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

void	lexer_free(t_lexer *lexer)
{
	lexer->next = NULL;
	source_free(&lexer->source);
}
