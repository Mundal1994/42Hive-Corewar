/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_register.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:56:33 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 13:56:33 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_register(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	statement->arguments[index].reg = (uint8_t) sym->num;
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	if (index < statement->op.argc - 1)
	{
		if (sym->type == LA_comma)
			return (OK);
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_EXPECT_SEP));
	}
	if (sym->type == LA_eol || sym->type == LA_com)
		return (OK);
	return (error(errorset(lexer->source.pos, sym->str),
			PARSER_EXPECT_EOL));
}
