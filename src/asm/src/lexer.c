/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:25:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 10:53:46 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexer_init(t_lexer *lexer, const char *filename)
{
	source_init(&lexer->source);
	source_read(&lexer->source, filename);
	source_next(&lexer->source);
}

void	lexer_free(t_lexer *lexer)
{
	source_free(&lexer->source);
}
