/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:50:38 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/25 22:17:16 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	reset(t_source *source)
{
	source->index = 0;
	source->pos = (t_pos){1, 0};
	source->curr = NULL;
	source->next = source->buffer.memory;
}

void	source_init(t_source *source)
{
	source->index = 0;
	source->pos = (t_pos){1, 0};
	source->curr = NULL;
	source->next = NULL;
	source->buffer.memory = NULL;
}

char	*source_peek(t_source *source)
{
	if (!source)
		return (NULL);
	if (!source->curr)
		reset(source);
	if (!source->next)
		return (NULL);
	return (source->next);
}

char	*source_next(t_source *source)
{
	if (!source)
		return (NULL);
	if (!source->curr)
		reset(source);
	if (!source->next)
		return (source->curr = NULL);
	source->curr = source->next;
	if (++source->index >= source->buffer.length)
		source->next = NULL;
	else
		source->next++;
	source->pos.r += *(source->curr) == NEWLINE_C;
	source->pos.c = (source->pos.c + 1) * (*(source->curr) != NEWLINE_C);
	return (source->curr);
}

void	source_free(t_source *source)
{
	if (source->buffer.memory)
		string_free(&source->buffer);
	ft_bzero(source, sizeof(*source));
}
