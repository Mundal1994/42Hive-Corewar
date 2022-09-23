/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:06:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/23 17:04:40 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define NEWLINE "\n"
# define NEWLINE_C '\n'
# define WHITESPACE " \t\n\v\f\r"
# define TABSPACE " \t"

typedef struct s_lexer
{
	t_source	source;
	char		*next;
}				t_lexer;

void	lexer_init(t_lexer *lexer);
//char	*lexer_next(t_lexer *lexer, const char *delim);
char	*lexer_token_trim_start(t_lexer *lexer, char *token);
void	lexer_free(t_lexer *lexer);

#endif
