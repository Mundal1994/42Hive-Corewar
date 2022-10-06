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

	sym->type = LA_cmdstr;
	start = source_next(source);
	if (!start)
		sym->type = LA_unknown;
	if (*start == '"')
	{
		source_next(source);
		return (string_clear(&sym->str), OK);
	}
	len = 1;
	while (source_next(source) && *(source->curr) != '"')
		++len;
	if (!source->curr)
		sym->type = LA_unknown;
	if (!string_replace_n(&sym->str, start, len))
		return (ERROR);
	if (sym->type == LA_unknown)
		return (error_no_str(errorset(source->pos, sym->str), LEXER_BAD_QUOTE));
	return (source_next(source), OK);
}
