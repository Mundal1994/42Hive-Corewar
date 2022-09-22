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

typedef struct s_lexer
{
	t_vec	buffer;
	char	*next;
	size_t	row;
}				t_lexer;

char	*lexer_buffer(t_lexer lexer);
char	*lexer_next_line(t_lexer *lexer);
void	lexer_free(t_lexer *lexer);

#endif
