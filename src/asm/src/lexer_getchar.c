/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:59 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 11:11:00 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getchar(t_source *source, t_symbols *sym)
{
	char	*curr;

	curr = source->curr;
	source_next(source);
	if (!string_replace_n(&sym->str, curr, 1))
		return (ERROR);
	return (OK);
}
