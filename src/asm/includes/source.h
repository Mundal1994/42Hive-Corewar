/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:33:19 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/28 17:08:18 by caruychen        ###   ########.fr       */
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

#ifndef SOURCE_H
# define SOURCE_H

# include <stdbool.h>
# include "Strings.h"

typedef struct s_pos
{
	size_t	r;
	size_t	c;
}		t_pos;

typedef struct s_source
{
	t_string	buffer;
	size_t		index;
	t_pos		pos;
	char		*curr;
	char		*next;
}				t_source;

void	source_init(t_source *source);
void	source_read(t_source *source, const char *filename);
char	*source_peek(t_source *source);
char	*source_next(t_source *source);
void	source_free(t_source *source);
bool	source_at_lineend(t_source source);
bool	source_at_linestart(t_source source);
char	*source_seekstart(t_source *source);
char	*source_buffer(t_source *source);

#endif
