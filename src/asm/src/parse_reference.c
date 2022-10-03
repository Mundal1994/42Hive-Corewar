/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reference.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:58:37 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/03 21:59:37 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_reference(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_arg_end(lexer, sym, statement, index));
}
