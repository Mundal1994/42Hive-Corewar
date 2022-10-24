/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_warn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:57:12 by cchen             #+#    #+#             */
/*   Updated: 2022/10/06 10:57:13 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Warnings for Lexer and Syntax analyser, but allows assembler to continue */

#include "ft_stdio.h"
#include "definitions.h"
#include "errors.h"

int	warning(t_errorset error, char *msg)
{
	ft_dprintf(2, "%sWarning: %s", YELLOW, NOCOLOR);
	ft_dprintf(2, "Found \"%s\" at [%ld:%ld]\n\t%s\n", error.str.memory,
		error.pos.r, error.pos.c, msg);
	return (OK);
}

int	warning_ret(char *msg)
{
	ft_dprintf(2, "%sWarning: %s%s\n", YELLOW, NOCOLOR, msg);
	return (OK);
}
