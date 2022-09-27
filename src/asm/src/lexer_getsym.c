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

static void	init(t_symbols *sym)
{
	sym->islabel = false;
	sym->isdirect = false;
	sym->type = LA_unknown;
	sym->num = 0;
}

static int	lexer_getstart(t_source *source, t_symbols *sym)
{
	char	*curr;

	curr = source->curr;
	if (is_wordch(*curr))
		return (sym->islabel = true, lexer_getword(source, sym));
	if (*curr == CMD_CHAR)
		return (sym->type = LA_cmd, lexer_getcmd(source, sym));
	sym->type = LA_unknown;
	return (lexer_getcomment(source, sym), ERROR);
}

int	lexer_getsym(t_lexer *lexer, t_symbols *sym)
{
	t_source	*source;
	char		*curr;

	init(sym);
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
		return (lexer_getstart(source, sym));
	if (ft_isdigit(*curr))
		return (sym->type = LA_num, lexer_getnumber(source, sym));
	if (is_wordch(*curr))
		return (lexer_getword(source, sym));
	if (*curr == LABEL_CHAR)
		return (sym->type = LA_ref, lexer_getreference(source, sym));
	if (*curr == DIRECT_CHAR)
		return (sym->isdirect = true, lexer_getdirect(source, sym));
	if (*curr == COMMENT_CHAR || *curr == ALT_COMMENT_CHAR)
		return (sym->type = LA_com, lexer_getcomment(source, sym));
	if (*curr == SEPARATOR_CHAR)
		return (sym->type = LA_comma, lexer_getchar(source, sym));
	if (*curr == '+')
		return (sym->type = LA_plus, lexer_getchar(source, sym));
	if (*curr == '-')
		return (sym->type = LA_minus, lexer_getchar(source, sym));
	if (*curr == '"')
		return (sym->tpe = LA_cmdstr, lexer_getquote(source, sym));
	lexer_getcomment(source, sym);
	return (ERROR);
}
