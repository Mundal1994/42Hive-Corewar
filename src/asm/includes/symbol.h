/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:52:41 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 12:52:43 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMBOL_H
# define SYMBOL_H

# include <stdbool.h>
# include "Strings.h"
# include "definitions.h"

# define DEFAULT_SYMBOL_LEN 128

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
	LA_plus,
	LA_comma,
	LA_minus
}		t_symtypes;

typedef struct s_symbols
{
	t_symtypes	type;
	t_string	str;
	int			num;
	t_arg_type	argtype;
}		t_symbols;

int		symbol_init(t_symbols *sym);
void	symbol_reset(t_symbols *sym);
void	symbol_free(t_symbols *sym);
char	*symbol_str(t_symbols *sym);

#endif
