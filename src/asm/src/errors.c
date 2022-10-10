/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:02:52 by cchen             #+#    #+#             */
/*   Updated: 2022/10/04 10:15:32 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "definitions.h"
#include "errors.h"

t_errorset	errorset(t_pos pos, t_string str)
{
	t_errorset	error;

	error.pos.r = pos.r - (*str.memory == '\n');
	error.pos.c = pos.c - str.length;
	error.str = str;
	return (error);
}

int	error_ret(char *msg)
{
	ft_dprintf(2, "%sError: %s%s\n", RED, NOCOLOR, msg);
	return (ERROR);
}

int	error_no_str(t_errorset error, char *msg)
{
	ft_dprintf(2, "%sError: %s", RED, NOCOLOR);
	ft_dprintf(2, "At line %ld\n\t%s\n", error.pos.r, msg);
	return (ERROR);
}

int	error(t_errorset error, char *msg)
{
	ft_dprintf(2, "%sError: %s", RED, NOCOLOR);
	ft_dprintf(2, "Found \"%s\" at [%ld:%ld]\n\t%s\n", error.str.memory,
		error.pos.r, error.pos.c, msg);
	return (ERROR);
}
