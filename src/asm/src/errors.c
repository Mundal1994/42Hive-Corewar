/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:02:52 by cchen             #+#    #+#             */
/*   Updated: 2022/09/28 17:17:08 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_errorset	errorset(t_pos pos, t_string str)
{
	t_errorset	error;

	error.pos.r = pos.r;
	error.pos.c = pos.c - str.length;
	error.str = str;
	return (error);
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

int	warning(t_errorset error, char *msg)
{
	ft_dprintf(2, "%sWarning: %s", YELLOW, NOCOLOR);
	ft_dprintf(2, "Found \"%s\" at [%ld:%ld]\n\t%s\n", error.str.memory,
		error.pos.r, error.pos.c, msg);
	return (OK);
}
