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

#include "asm.h"

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
