/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:09:42 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/18 10:46:07 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "validator.h"
#include "errors.h"

static int	is_valid_extension(char *arg)
{
	char	*extension;

	extension = ft_strrchr(arg, '.');
	return (extension && !ft_strcmp(extension, EXTENSION_IN));
}

void	validate_arguments(int argc, char **argv)
{
	if (argc == 2 && is_valid_extension(argv[1]))
		return ;
	if (argc == 2)
		error_ret(ARG_INVALID_EXT);
	exit_error_str(MSG_USAGE);
}
