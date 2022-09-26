/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:01:44 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 11:01:46 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

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

void	exit_error(void);
void	exit_error_str(char *str);
int		error(char *msg);

#endif
