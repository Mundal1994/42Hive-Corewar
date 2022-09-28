/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:01:44 by cchen             #+#    #+#             */
/*   Updated: 2022/09/28 17:18:35 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "definitions.h"

# define YELLOW "\033[0;33m"
# define NOCOLOR "\033[0m"

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
int			error(char *msg);
t_errorset	errorset(t_pos pos, t_string str);
int			warning(t_errorset error, char *msg);

#endif
