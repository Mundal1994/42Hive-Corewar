/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:16:22 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 11:16:23 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getquote(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	start = source_next(source);
	if (!start)
		return (ERROR);
	if (*start == '"')
		return (string_clear(&sym->str), OK);
	len = 1;
	while (source_next(source) && *(source->curr) != '"')
		++len;
	if (!source->curr)
		return (ERROR);
	return (source_next(source), OK);
}
