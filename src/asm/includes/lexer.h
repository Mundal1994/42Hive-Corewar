/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:06:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 23:12:44 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "symbol.h"
# include "source.h"
# include "op.h"
# include "libft.h"

typedef struct s_lexer
{
	t_source	source;
}			t_lexer;

void	lexer_init(t_lexer *lexer, const char *filename);
void	lexer_free(t_lexer *lexer);

/* Returns next symbol on the current source line. Sets errors if necessary
   and returns sym = sym.type = unknowwn if no valid symbol can be
   recognised */
int		lexer_getsym(t_lexer *lexer, t_symbols *sym);
int		lexer_getword(t_source *source, t_symbols *sym);
int		lexer_getcmd(t_source *source, t_symbols *sym);
int		lexer_getcomment(t_source *source, t_symbols *sym);
int		lexer_getdirect(t_source *source, t_symbols *sym);
int		lexer_getnumber(t_source *source, t_symbols *sym);
int		lexer_getreference(t_source *source, t_symbols *sym);
int		lexer_getquote(t_source *source, t_symbols *sym);
int		lexer_getchar(t_source *source, t_symbols *sym);

bool	is_wordch(char c);
bool	is_register(const char *str);

#endif
