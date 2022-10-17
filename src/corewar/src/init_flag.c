/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:11:44 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 12:11:46 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	set_flag_minus(t_info *info)
{
	int	i;

	i = 0;
	while (i < FLAG_COUNT)
	{
		info->flag[i] = -1;
		++i;
	}
}

static int	set_flag_true(t_info *info, int type)
{
	info->flag[type] = TRUE;
	return (TRUE);
}

static int	check_int_flag(char *str, t_info *info)
{
	if (!ft_strcmp(str, "-dump") || !ft_strcmp(str, "-d"))
		return (set_flag_true(info, D_FLAG));
	if (!ft_strcmp(str, "-dc"))
		return (set_flag_true(info, DC_FLAG));
	if (!ft_strcmp(str, "-di"))
		return (set_flag_true(info, DI_FLAG));
	if (!ft_strcmp(str, "-c"))
		return (set_flag_true(info, C_FLAG));
	if (!ft_strcmp(str, "-v"))
		return (set_flag_true(info, V_FLAG));
	return (FALSE);
}

static int	check_flag_with_no_digit(char *str, t_info *info)
{
	if (!ft_strcmp(str, "-a"))
		return (set_flag_true(info, A_FLAG));
	if (!ft_strcmp(str, "-i"))
		return (set_flag_true(info, I_FLAG));
	if (!ft_strcmp(str, "-o"))
		return (set_flag_true(info, I_FLAG));
	return (FALSE);
}

int	init_flags(int argc, char **argv, t_info *info)
{
	int	i;

	set_flag_minus(info);
	if (check_flag_with_no_digit(argv[1], info))
		return (TRUE);
	if (check_int_flag(argv[1], info))
	{
		if (argc > 3 && ft_isnumber(argv[2]))
		{
			i = 0;
			while (i < FLAG_COUNT)
			{
				if (info->flag[i] == TRUE)
					info->flag[i] = ft_atoi(argv[2]);
				++i;
			}
			return (2);
		}
		return (ERROR);
	}
	info->flag[NO_FLAG] = TRUE;
	return (0);
}
