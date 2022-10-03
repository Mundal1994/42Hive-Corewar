/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_indirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:18:46 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 14:18:47 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_indirect(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	statement->arguments[index].ind = (uint16_t) sym->num;
	if (sym->argtype & T_LAB)
	{
		ft_printf("Lab: %s", sym->str.memory);
		if (lexer_next(lexer, sym) == ERROR)
			return (ERROR);
		return (parse_arg_end(lexer, sym, statement, index));
	}
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_numeric(statement, lexer, sym, index));
}
