/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:45:13 by cchen             #+#    #+#             */
/*   Updated: 2022/09/23 11:37:04 by caruychen        ###   ########.fr       */
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
