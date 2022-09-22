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

char	*lexer_buffer(t_lexer lexer)
{
	char	*str;

	str = (char *) lexer.buffer.memory;
	return (str);
}

void	lexer_free(t_lexer *lexer)
{
	if (lexer->buffer.memory)
		vec_free(&lexer->buffer);
	lexer->next = NULL;
}
