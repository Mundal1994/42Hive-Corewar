/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getnumber.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:10:08 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 16:00:17 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getnumber(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	sym->type = LA_num;
	sym->argtype |= T_IND * !(sym->argtype & T_DIR);
	start = source->curr;
	if (is_operator(*start) && !ft_isdigit(*source_peek(source)))
		return (error_no_str(errorset(source->pos, sym->str),
				LEXER_MISSING_NUM));
	len = 1;
	while (source_next(source) && ft_isdigit(*(source->curr)))
		++len;
	if (!string_replace_n(&sym->str, start, len))
		return (ERROR);
	return (sym->num = ft_atoi(symbol_str(sym)), OK);
}
