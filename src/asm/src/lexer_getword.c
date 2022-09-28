/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getword.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:38:47 by cchen             #+#    #+#             */
/*   Updated: 2022/09/28 17:05:46 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	set_label(t_source *source, t_symbols *sym, char *start,
		size_t len)
{
	string_replace_n(&sym->str, start, len);
	source_next(source);
	return (OK);
}

static int	set_register(t_source source, t_symbols *sym)
{
	sym->num = ft_atoi(sym->str.memory + 1);
	if (sym->num < 1 || sym->num > REG_NUMBER)
		return (warning(errorset(source.pos, sym->str), REG_WARNING));
	return (sym->type = LA_reg, OK);
}

int	lexer_getword(t_source *source, t_symbols *sym)
{
	size_t	len;	
	char	*curr;
	char	*start;

	curr = source->curr;
	start = source->curr;
	len = 0;
	while (curr && (is_wordch(*curr) || *curr == LABEL_CHAR))
	{
		if (*curr == LABEL_CHAR && sym->type == LA_label)
			return (set_label(source, sym, start, len));
		if ((*curr == LABEL_CHAR || *curr == '_') && sym->type != LA_label)
			sym->type = LA_unknown;
		curr = source_next(source);
		++len;
	}
	string_replace_n(&sym->str, start, len);
	if (is_register(sym->str.memory))
		return (set_register(*source, sym));
	if (sym->type == LA_unknown)
		return (ERROR);
	return (sym->type = LA_instr, OK);
}
