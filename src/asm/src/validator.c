/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:09:42 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/18 10:30:00 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_arguments(int argc, char **argv)
{
	char	*extension;

	if (argc != 2)
	{
		ft_putendl_fd(MSG_USAGE, 2);
		exit(EXIT_FAILURE);
	}
	extension = ft_strrchr(argv[1], '.');
	if (extension && !ft_strcmp(extension, EXTENSION_IN))
		return ;
	ft_putendl_fd(ERR_MSG_INVALID_EXT, 2);
	ft_putendl_fd(MSG_USAGE, 2);
	exit(EXIT_FAILURE);
}
