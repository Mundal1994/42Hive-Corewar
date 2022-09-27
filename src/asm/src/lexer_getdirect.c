/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getdirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:50:14 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 09:50:15 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexer_getdirect(t_source *source, t_symbols *sym)
{
	char	*next;

	next = source_next(source);
	if (next && next == LABEL_CHAR)
		return (sym->type = LA_ref, lexer_getreference(source, sym));
	if (next && ft_isdigit(*next))
		return (sym->type = LA_num, lexer_getnumber(source, sym));
	lexer_getcomment(source, sym);
	return (ERROR);
}
