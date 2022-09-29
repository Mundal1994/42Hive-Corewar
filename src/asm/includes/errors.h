/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:01:44 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 09:39:45 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "definitions.h"

# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define NOCOLOR "\033[0m"

# define LEXER_BAD_INSTR "Illegal character found in instruction"
# define LEXER_BAD_REF "Illegal or empty label reference"
# define LEXER_BAD_QUOTE "Quote string incomplete, please close end \
of quote string"
# define LEXER_UNKNOWN "Encountered an unknown token. pls fix :("
# define REG_WARNING "Register number out of bounds, may lead to\
 Virtual Machine memory errors"

typedef enum s_errors
{
	ASM_invalidcode,
	ASM_undefinedlabel,
	ASM_invalidaddress,
	ASM_unlabelled,
	ASM_hasaddress,
	ASM_noaddress,
	ASM_ecessfields,
	ASM_mismatched,
	ASM_nonalpha,
	ASM_badlabel,
	ASM_invalidchar,
	ASM_invaliduote,
	ASM_overflow
}			t_errors;

typedef struct s_errorset
{
	t_pos		pos;
	t_string	str;
}		t_errorset;

void		exit_error(void);
void		exit_error_str(char *str);
int			error_no_str(t_errorset error, char *msg);
int			error(t_errorset error, char *msg);
t_errorset	errorset(t_pos pos, t_string str);
int			warning(t_errorset error, char *msg);

#endif
