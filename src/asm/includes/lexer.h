/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:06:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/25 11:27:14 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define NEWLINE "\n"
# define NEWLINE_C '\n'
# define WHITESPACE " \t\n\v\f\r"
# define TABSPACE " \t"

# include <stdbool.h>

typedef enum s_symtypes
{
	LA_UNKNOWN,
	LA_EOFSYM,
	LA_EOLSYM,
	LA_IDSYM,
	LA_NUMSYM,
	LA_CMDSYM,
	LA_COMSYM,
	LA_COMMASYM,
	LA_PLUSSYM,
	LA_MINUSSYM
}		t_symtypes;

typedef struct s_symbols
{
	bool		is_label;
	t_symtypes	sym;
	t_vec		str;
	int			num;
}		t_symbols;

typedef struct s_lexer
{
	t_source	source;
	char		*next;
}			t_lexer;

void	lexer(t_lexer *lexer);
void	lexer_getsym(t_lexer *lexer, t_symbols &sym);
void	lexer_free(t_lexer *lexer);

#endif
