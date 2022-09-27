/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:50:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 08:50:47 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	is_wordch(char c)
{
	return (ft_islower(c) || ft_isdigit(c) || c == '_');
}

bool	is_register(const char *str)
{
	return (*str == 'r' && ft_isnumber(str + 1));
}
