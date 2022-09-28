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

void	exit_error(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

void	exit_error_str(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (ERROR);
}

t_errorset	errorset(t_pos pos, t_string str)
{
	t_errorset	error;

	error.pos.r = pos.r;
	error.pos.c = pos.c - str.length;
	error.str = str;
	return (error);
}

int	warning(t_errorset error, char *msg)
{
	ft_dprintf(2, "%sWarning: %s", YELLOW, NOCOLOR);
	ft_dprintf(2, "Found \"%s\" at [%ld:%ld]\n\t%s\n", error.str.memory,
		error.pos.r, error.pos.c, msg);
	return (OK);
}
