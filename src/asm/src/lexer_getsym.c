/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:08:01 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 23:12:37 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer_getsym(t_lexer *lexer, t_symbols *sym)
{
	t_source	*source;
	char		*curr;

	sym->num = 0;
	source = &lexer->source;
	source_seekstart(source);
	curr = source->curr;
	if (!curr)
		return (sym->type = LA_eof, OK);
	if (source_at_lineend(*source))
	{
		source_next(source);
		return (sym->type = LA_eol, OK);
	}
	if (source_at_linestart(*source))
	{
		if (is_wordch(*curr))
		{
			sym->islabel = true;
			return (lexer_getword(lexer, sym));
		}
		if (*curr == CMD_CHAR)
			return (lexer_getcmd(lexer, sym));
		lexer_getcomment(lexer, sym);
		return (sym->type = LA_unknown, ERROR);
	}
	if (is_wordch(*curr))
		return (lexer_getword(lexer, sym));
	if (*curr == COMMENT_CHAR || *curr == ALT_COMMENT_CHAR)
		return (sym->type = LA_com, lexer_getcomment(lexer, sym));
}
