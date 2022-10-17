/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:50:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/28 16:20:12 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include <stdbool.h>

/* Is the current char a lower-case alphanumeric, or '_'? */
bool	is_wordch(char c)
{
	return (ft_islower(c) || ft_isdigit(c) || c == '_');
}

/* Is the current string a register type? e.g. r1 */
bool	is_register(const char *str)
{
	return (*str == 'r' && ft_isnumber(str + 1));
}

/* Is the character a mathematical operator? + or - */
bool	is_operator(char c)
{
	return (c == '+' || c == '-');
}
