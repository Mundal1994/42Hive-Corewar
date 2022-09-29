/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:06:40 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 11:06:42 by cchen            ###   ########.fr       */
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
