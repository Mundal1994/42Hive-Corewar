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

static int	middle_arguments(t_lexer *lexer, t_symbols *sym)
{
	if (sym->type == LA_comma)
		return (OK);
	if (sym->type == LA_eol || sym->type == LA_com)
		return (error_no_str(errorset(lexer->source.pos, sym->str),
				PARSER_INSUF_ARG));
	return (error(errorset(lexer->source.pos, sym->str),
			PARSER_EXPECT_SEP));
}

static int	end_arguments(t_lexer *lexer, t_symbols *sym)
{
	if (sym->type == LA_eol || sym->type == LA_com)
		return (OK);
	if (sym->type == LA_comma)
		return (error(errorset(lexer->source.pos, sym->str),
				PARSER_TOO_MANY_ARGS));
	return (error(errorset(lexer->source.pos, sym->str),
			PARSER_EXPECT_EOL));
}

int	parse_arg_end(t_lexer *lexer, t_symbols *sym, t_statement *statement,
		uint8_t index)
{
	if (index < statement->op.argc - 1)
		return (middle_arguments(lexer, sym));
	return (end_arguments(lexer, sym));
}
