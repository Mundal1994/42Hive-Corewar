/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getreference.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:52:44 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 09:52:45 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getreference(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	start = source_next(source);
	if (!start || !is_wordch(*start))
		sym->type = LA_unknown;
	len = 1;
	while (source_next(source) && is_wordch(*(source->curr)))
		++len;
	if (!string_replace_n(source, start, len))
		return (ERROR);
	if (sym->type == LA_unknown)
		return (ERROR);
	return (OK);
}
