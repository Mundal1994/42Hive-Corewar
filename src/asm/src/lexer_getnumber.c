/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getnumber.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:10:08 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 10:10:10 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getnumber(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	sym->type = LA_num;
	start = source->curr;
	len = 1;
	while (source_next(source) && ft_isdigit(*(source->curr)))
		++len;
	if (!string_replace_n(&sym->str, start, len))
		return (ERROR);
	return (sym->num = ft_atoi(sym->str.memory), OK);
}
