/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:50:38 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 12:50:39 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symbol.h"

int	symbol_init(t_symbols *sym)
{
	sym->isdirect = false;
	sym->type = LA_unknown;
	sym->num = 0;
	sym->argtype = 0;
	if (!string_new(&sym->str, DEFAULT_SYMBOL_LEN))
		return (ERROR);
	return (OK);
}

void	symbol_reset(t_symbols *sym)
{
	sym->isdirect = false;
	sym->type = LA_unknown;
	sym->num = 0;
	sym->argtype = 0;
}

void	symbol_free(t_symbols *sym)
{
	symbol_reset(sym);
	string_free(&sym->str);
}

char	*symbol_str(t_symbols *sym)
{
	return (sym->str.memory);
}
