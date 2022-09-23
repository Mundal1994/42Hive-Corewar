/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:14:31 by cchen             #+#    #+#             */
/*   Updated: 2022/09/23 11:36:30 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_valid_cmd(char *str, char *cmd)
{
	char	*next;
	char	*token;

	next = NULL;
	token = ft_strtok_r(str, TABSPACE, &next);
	return (token
		&& ft_strequ(token, cmd)
		&& ft_strtok_r(NULL, TABSPACE, &next) == NULL);
}

static char	*get_string(t_lexer *lexer, char *cmd, long max_len)
{
	char		*token;
	char		*delim;

	delim = "\"";
	token = lexer_next(lexer, delim);
	token = lexer_token_trim_start(lexer, token);
	if (!is_valid_cmd(token, cmd))
		return (syntax_error(ERR_MSG_BAD_CMD, token, *lexer), NULL);
	if (*lexer->next == '"')
		return (*lexer->next = '\0', lexer->next++);
	token = lexer_next(lexer, delim);
	if (lexer->next - token - 1 > max_len)
		return (syntax_error(ERR_MSG_STR_TOO_LONG, token, *lexer), NULL);
	return (token);
}

static int	parse_line(char *dst, t_lexer *lexer,
	char *cmd, long max_len)
{
	char	*token;
	size_t	len;

	token = get_string(lexer, cmd, max_len);
	if (!token)
		return (ERROR);
	len = lexer->next - token;
//	lexer->row += ft_count_charn(token, NEWLINE_C, len);
	return (ft_memcpy(dst, token, len), OK);
}

int	parse_header(t_header *header, t_lexer *lexer)
{
	if (parse_line(header->prog_name, lexer,
			NAME_CMD_STRING, PROG_NAME_LENGTH) == ERROR
		|| parse_line(header->comment, lexer,
			COMMENT_CMD_STRING, COMMENT_LENGTH) == ERROR)
		return (ERROR);
	return (OK);
}
