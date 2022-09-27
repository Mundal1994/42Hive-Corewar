/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:08:03 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/23 22:41:06 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	source_at_lineend(t_source source)
{
	return (!source.curr || *source.curr == '\n' || *source.curr == '\0');
}

bool	source_at_linestart(t_source source)
{
	char	*start;

	if (source.pos.c == 1)
		return (true);
	if (source.pos.c == 0)
		return (false);
	start = source.curr - (source.pos.c - 1);
	while (start < source.curr && ft_strchr(TABSPACE, *start))
		++start;
	return (start == source.curr);
}

char	*source_seekstart(t_source *source)
{
	if (!source->curr)
		source_next(source);
	while (ft_strchr(TABSPACE, *(source->curr)) && !source_at_endline(*source))
		source_next(source);
	return (source->curr);
}
