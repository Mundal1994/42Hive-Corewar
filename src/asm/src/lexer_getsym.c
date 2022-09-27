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

static int	lexer_getstart(t_source *source, t_symbols *sym)
{
	char	*curr;

	curr = source->curr;
	if (is_wordch(*curr))
		return (sym->type = LA_label, lexer_getword(source, sym));
	if (*curr == CMD_CHAR)
		return (sym->type = LA_cmd, lexer_getcmd(source, sym));
	return (lexer_getcomment(source, sym));
}

static int	lexer_end(t_source *source, t_symbols *sym)
{
	char	*curr;

	curr = source->curr;
	if (!curr)
		return (sym->type = LA_eof, DONE);
	source_next(source);
	return (sym->type = LA_eol, OK);
}

static int	getter_index(const char *curr)
{
	if (!curr || *curr < ' ' || *curr > '@')
		return (0);
	return (*curr - ' ');
}

int	lexer_getsym(t_lexer *lexer, t_symbols *sym)
{
	t_source		*source;
	t_lexer_getter	getter;
	char			*curr;

	symbol_reset(sym);
	source = &lexer->source;
	source_seekstart(source);
	curr = source->curr;
	if (source_at_lineend(*source))
		return (lexer_end(source, sym));
	if (source_at_linestart(*source))
		return (lexer_getstart(source, sym));
	getter = g_lexer_getter[getter_index(curr)];
	if (getter)
		return (getter(source, sym));
	if (is_wordch(*curr))
		return (sym->type = LA_instr, lexer_getword(source, sym));
	return (lexer_getcomment(source, sym));
}
