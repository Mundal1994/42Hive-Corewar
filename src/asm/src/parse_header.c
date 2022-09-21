/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:14:31 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 12:14:33 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_valid_name_cmd(char *str)
{
	char	*next;
	char	*delim;
	char	*token;
	size_t	len;

	token = ft_strchr(str, '.');
	len = token - str;
	if (!token || ft_strspn(str, WHITESPACE) != len)
		return (FALSE);
	delim = " \t";
	token = ft_strtok_r(token, delim, &next);
	return (ft_strequ(NAME_CMD_STRING, token)
		&& ft_strtok_r(NULL, delim, &next) == NULL);
}

static char	*parse_name(t_lexer *lexer)
{
	char	*str;
	char	*delim;

	delim = "\"";
	str = ft_strtok_r(lexer_buffer(*lexer), delim, &lexer->next);
	if (!is_valid_name_cmd(str))
		return (error(ERR_MSG_INVALID_NAME), NULL);
	if (*lexer->next == '"')
		return (*lexer->next = '\0', lexer->next++);
	str = ft_strtok_r(NULL, delim, &lexer->next);
	if (lexer->next - str - 1 > PROG_NAME_LENGTH)
		return (error(ERR_MSG_NAME_TOO_LONG), NULL);
	return (str);
}

int	parse_header(t_header *header, t_lexer *lexer)
{
	char	*token;

	token = parse_name(lexer);
	if (!token)
		return (ERROR);
	ft_memcpy(header->prog_name, token, lexer->next - token);
	return (OK);
}
