/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getcomment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:52:44 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 08:52:45 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getcomment(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	start = source->curr;
	len = 1;
	while (source_next(source) && !source_at_lineend(*source))
		++len;
	if (string_replace_n(&sym->str, start, len))
		return (OK);
	return (ERROR);
}
