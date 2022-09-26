/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:08:01 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 11:08:02 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	is_word(char c)
{
	return (ft_islower(c) || ft_isdigit(c) || c == '_' || c == ':' || c == '%');
}

void	lexer_getsym(t_lexer *lexer, t_symbols *sym)
{
	t_source	*source;

	sym->num = 0;
	source = &lexer->source;
	source_seekstart(source);
	sym->islabel = source_at_linestart(*source) && *source->curr
			&& *source->curr != COMMENT_CHAR
			&& *source->curr != ALT_COMMENT_CHAR
			&& *source->curr != CMD_CHAR;
	if (*source->curr == '\0')
	{
		sym.type = LA_eof;
		return;
	}
	if (source_at_lineend(*source))
	{
		sym.type = LA_eol;
		source_next(source);
		return;
	}
	if (is_label_char(*source->curr))
		_lexer_getword(lexer, sym);
	if (*source->curr == CMD_CHAR)
	{
		sym.type = LA_cmd;
		_lexer_getcmd(lexer, sym);
	}
}
