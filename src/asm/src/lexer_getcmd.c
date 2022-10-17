/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:51:54 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 08:51:55 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "definitions.h"
#include "lexer.h"

/* Emits the command token if the word preceded by a '.' and contains only
 * alphanumeric characters. This function is only called if the current token
 * starts with '.' */
int	lexer_getcmd(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	start = source->curr;
	len = 1;
	while (ft_isalnum(*source_next(source)))
		++len;
	if (string_replace_n(&sym->str, start, len))
		return (OK);
	return (ERROR);
}
