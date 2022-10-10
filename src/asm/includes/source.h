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
