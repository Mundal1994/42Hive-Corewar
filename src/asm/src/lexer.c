/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:25:53 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 17:17:07 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** *
 * Lexical analysis
 *   - Deals with  the "words"
 *   - Converts the sequence of characters into a sequence symbols (tokens).
 *   - The source characters can be assembled into one of 14 different types
 *     of symbols, such as a label, comma, operation, argument etc. The full
 *     list of symbol types can be found in symbol.h
 *   - The lexer does not understand any grammatical context, it just tells you
 *     what the next word is.
 *   - Reports an error if it finds any unrecognised symbols. So the client
 *     won't have to worry about "word correctness"
 *
 * The main interface to the lexer is the "lexer_next" function, found in
 * lexer_next.c
 *
 * Function found in this file serve mainly as utility functions.
 * ************************************************************************* */

#include "definitions.h"
#include "lexer.h"

/* Initialises source data, and reads text into the buffer */
void	lexer_init(t_lexer *lexer, const char *filename)
{
	source_init(&lexer->source);
	source_read(&lexer->source, filename);
	source_next(&lexer->source);
}

/* Frees memory from source */
void	lexer_free(t_lexer *lexer)
{
	source_free(&lexer->source);
}

/* If the next symbol is end of the line, searches for the start of the
 * next line. Otherwise, just returns the next symbol */
int	lexer_nextline(t_lexer *lexer, t_symbols *sym)
{
	int	res;

	res = lexer_next(lexer, sym);
	while (res == OK)
	{
		if (sym->type != LA_eol && sym->type != LA_com)
			break ;
		res = lexer_next(lexer, sym);
	}
	return (res);
}
