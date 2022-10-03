/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_direct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:18:35 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 14:18:36 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	is_endof_arg(t_symtypes type, uint8_t argc, uint8_t index)
{
	if (index < argc - 1 && type == LA_comma)
		return (true);
	if (index == argc - 1 && (type == LA_eol || type == LA_com))
		return (true);
	return (false);
}

int	parse_direct(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	statement->arguments[index].dir = (uint32_t) sym->num;
	if (sym->argtype & T_LAB)
		ft_printf("Lab: %s", sym->str.memory);
	while (is_endof_arg)
	{
	}
}
