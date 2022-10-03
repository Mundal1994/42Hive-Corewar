/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:58:53 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 18:37:05 by caruychen        ###   ########.fr       */
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

int	parse_line(t_lexer *lexer, t_symbols *sym)
{
	while (lexer_next(lexer, sym) == OK && sym->type > LA_eol)
	{
	}
}

int	parse(t_lexer *lexer)
{
	t_symbols	sym;

	parse_init(lexer, &sym);
	parse_header(lexer, &sym);
	symbol_free(&sym);
	return (OK);
}
