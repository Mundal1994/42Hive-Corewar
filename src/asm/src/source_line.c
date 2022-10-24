/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:08:03 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/27 11:33:37 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include "source.h"

/* Indicates whether the source handler is at the end of a line */
bool	source_at_lineend(t_source source)
{
	return (!source.curr || *source.curr == '\n' || *source.curr == '\0');
}

/* Indicates whether the source handler is at the start of a line */
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

/* Seeks the start of the current line */
char	*source_seekstart(t_source *source)
{
	if (!source->curr)
		return (NULL);
	while (!source_at_lineend(*source) && ft_strchr(TABSPACE, *(source->curr)))
		source_next(source);
	return (source->curr);
}

/* Returns pointer to the buffered string */
char	*source_buffer(t_source *source)
{
	return (source->buffer.memory);
}
