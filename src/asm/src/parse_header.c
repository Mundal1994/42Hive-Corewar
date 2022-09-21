/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:14:31 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 21:12:31 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_valid_cmd(char *str, char *cmd)
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
	return (ft_strequ(token, cmd)
		&& ft_strtok_r(NULL, delim, &next) == NULL);
}

static char	*parse_header_line(t_lexer *lexer, char *cmd, long len)
{
	char		*str;
	char		*delim;
	char		*buffer;

	delim = "\"";
	buffer = NULL;
	if (lexer->next == NULL)
		buffer = lexer_buffer(*lexer);
	str = ft_strtok_r(buffer, delim, &lexer->next);
	if (!is_valid_cmd(str, cmd))
		return (error(ERR_MSG_BAD_CMD), NULL);
	if (*lexer->next == '"')
		return (*lexer->next = '\0', lexer->next++);
	str = ft_strtok_r(NULL, delim, &lexer->next);
	if (lexer->next - str - 1 > len)
		return (error(ERR_MSG_STR_TOO_LONG), NULL);
	return (str);
}

static int	parse_line(char *dst, t_lexer *lexer,
	char *cmd, long len)
{
	char	*token;

	token = parse_header_line(lexer, cmd, len);
	if (!token)
		return (ERROR);
	return (ft_memcpy(dst, token, lexer->next - token), OK);
}

int	parse_header(t_header *header, t_lexer *lexer)
{
	return (parse_line(header->prog_name, lexer,
			NAME_CMD_STRING, PROG_NAME_LENGTH) == OK
		&& parse_line(header->comment, lexer,
			COMMENT_CMD_STRING, COMMENT_LENGTH) == OK);
}
