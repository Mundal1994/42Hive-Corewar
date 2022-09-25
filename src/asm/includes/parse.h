/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:19:06 by cchen             #+#    #+#             */
/*   Updated: 2022/09/25 17:53:16 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>

typedef enum s_termkinds
{
	SA_absent,
	SA_numeric,
	SA_alphameric,
	SA_comma,
	SA_plus,
	SA_minus,
	SA_star
}		t_termkinds;

typedef struct s_terms
{
	t_termkinds	kind;
	int			number;
	t_alfa		name;
}		t_terms;

/* Entries are stored in a dynamic array, allowing for varying number */
typedef struct t_vec	t_addresses;

/* Source text, unpacked into field */
typedef struct s_unpackedlines
{
	bool		labelled;
	t_alfa		labfield;
	t_alfa		mnemonic;
	t_addresses	address;
	t_string	comment;

}		t_unpackedlines;

void	parser(t_ast *ast, t_lexer *lexer);
int		parser_header(t_header *header, t_lexer *lexer);

#endif
