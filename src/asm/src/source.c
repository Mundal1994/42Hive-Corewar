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

/* ************************************************************************** *
 * The fundamental phase of the parser is the source character handler.
 * The source handler scans the source text, returning a character at a time
 * and analyses the source into lines.
 *
 * Client procedures should not have to worry about keeping track of source
 * text position.
 *
 * The t_source data structure has the following fields:
 * 1. buffer (t_string):	Points to the source text stored in main memory
 * 2. index:				Current index position of the source text
 * 3. pos -> {r, c}:		Row and column of the current position.
 * 4. curr:					Pointer to the current character.
 * 5. next:					Pointer to the next character
 * 
 * The primary interface for t_source is the 'source_next' function which:
 *   - Returns the next character.
 *   - Updates current position data in the t_source struct.
 * ************************************************************************* */

#include "definitions.h"
#include "source.h"

/* Initialises meta-data fields in source */
void	source_init(t_source *source)
{
	source->index = 0;
	source->pos = (t_pos){1, 0};
	source->curr = NULL;
	source->next = NULL;
	source->buffer.memory = NULL;
}

/* Resets meta-data fields in source */
static void	reset(t_source *source)
{
	source->index = 0;
	source->pos = (t_pos){1, 0};
	source->curr = NULL;
	source->next = source_buffer(source);
}

/* Returns the next character without moving the source pointer forward */
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

/* Returns the next character, and moves the source pointer forward */
char	*source_next(t_source *source)
{
	int	is_newline;

	if (!source)
		return (NULL);
	if (!source->curr)
		reset(source);
	if (!source->next)
		return (source->curr = NULL);
	is_newline = (source->curr && *(source->curr) == NEWLINE_C);
	source->pos.r += is_newline;
	source->pos.c = source->pos.c * !is_newline + 1;
	source->curr = source->next;
	if (++source->index >= source->buffer.length)
		source->next = NULL;
	else
		source->next++;
	return (source->curr);
}

/* Frees allocated source data memory */
void	source_free(t_source *source)
{
	if (source_buffer(source))
		string_free(&source->buffer);
	ft_bzero(source, sizeof(*source));
}
