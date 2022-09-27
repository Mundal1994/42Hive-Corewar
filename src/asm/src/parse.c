/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:58:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 14:38:44 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	parse_init(t_lexer *lexer, t_symbols *sym)
{
	if (symbol_init(sym) == OK)
		return ;
	lexer_free(lexer);
	exit_error();
}

int	parse(t_lexer *lexer)
{
	t_symbols	sym;

	parse_init(lexer, &sym);
	while (lexer_next(lexer, &sym) == OK)
	{
		ft_printf("type: %d, id_direct: %d, num: %d, str: %s\n",
			sym.type, sym.isdirect, sym.num, sym.str.memory);
	}
	symbol_free(&sym);
	return (OK);
}
