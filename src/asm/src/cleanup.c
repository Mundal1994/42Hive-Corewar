/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:45:13 by cchen             #+#    #+#             */
/*   Updated: 2022/09/19 10:51:50 by cchen            ###   ########.fr       */
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

int	syntax_error(char *msg, char *token, t_lexer lexer)
{
	ssize_t	row;
	ssize_t	col;

	start = token - lexer_buffer(lexer);
	end = lexer.next - token;
	ft_printf("%s at [%ld:%ld] \"%s\"\n", msg, start, end, token);
	return (ERROR);
}
