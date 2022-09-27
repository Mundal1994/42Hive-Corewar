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
	sym->type = LA_unknown;
	return (lexer_getcomment(source, sym), ERROR);
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

int	lexer_getsym(t_lexer *lexer, t_symbols *sym)
{
	t_source	*source;
	char		*curr;

	symbol_reset(sym);
	source = &lexer->source;
	source_seekstart(source);
	curr = source->curr;
	if (source_at_lineend(*source))
		return (lexer_end(source, sym));
	if (*curr == COMMENT_CHAR || *curr == ALT_COMMENT_CHAR)
		return (sym->type = LA_com, lexer_getcomment(source, sym));
	if (source_at_linestart(*source))
		return (lexer_getstart(source, sym));
	if (ft_isdigit(*curr))
		return (sym->type = LA_num, lexer_getnumber(source, sym));
	if (is_wordch(*curr))
		return (sym->type = LA_instr, lexer_getword(source, sym));
	if (*curr == LABEL_CHAR)
		return (sym->type = LA_ref, lexer_getreference(source, sym));
	if (*curr == DIRECT_CHAR)
		return (sym->isdirect = true, lexer_getdirect(source, sym));
	if (*curr == SEPARATOR_CHAR)
		return (sym->type = LA_comma, lexer_getchar(source, sym));
	if (*curr == '+')
		return (sym->type = LA_plus, lexer_getchar(source, sym));
	if (*curr == '-')
		return (sym->type = LA_minus, lexer_getchar(source, sym));
	if (*curr == '"')
		return (sym->type = LA_cmdstr, lexer_getquote(source, sym));
	lexer_getcomment(source, sym);
	return (ERROR);
}
