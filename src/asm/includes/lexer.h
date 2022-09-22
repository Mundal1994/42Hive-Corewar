/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:06:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/21 14:06:48 by cchen            ###   ########.fr       */
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
	t_vec	buffer;
	char	*next;
	size_t	row;
}				t_lexer;

char	*lexer_buffer(t_lexer lexer);
char	*lexer_next(t_lexer *lexer, const char *delim);
char	*lexer_token_trim_start(t_lexer *lexer, char *token);
void	lexer_free(t_lexer *lexer);

#endif
