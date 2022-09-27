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

# include <stdbool.h>
# include "Strings.h"
# include "source.h"
# include "op.h"
# include "definitions.h"
# include "libft.h"

typedef enum s_symtypes
{
	LA_unknown,
	LA_eof,
	LA_eol,
	LA_label,
	LA_instr,
	LA_reg,
	LA_ref,
	LA_num,
	LA_cmd,
	LA_cmdstr,
	LA_com,
	LA_comma,
	LA_plus,
	LA_minus
}		t_symtypes;

typedef struct s_symbols
{
	bool		isdirect;
	t_symtypes	type;
	t_string	str;
	int			num;
}		t_symbols;

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
