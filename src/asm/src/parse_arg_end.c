/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:12:48 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 16:12:50 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_arg_end(t_lexer *lexer, t_symbols *sym, t_statement *statement,
		uint8_t index)
{
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
