/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:36:40 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/04 10:58:34 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <stddef.h>
# include <stdint.h>

/* ****************************************************************************
   SHARED DEFINITIONS
******************************************************************************/

/* Return Values */
# define ERROR	-1
# define OK		1
# define DONE	0

# define NEWLINE_C '\n'
# define TABSPACE " \t"

typedef struct s_pos
{
	size_t	r;
	size_t	c;
}		t_pos;

typedef union s_arg
{
	uint8_t		reg;
	uint16_t	ind;
	uint32_t	dir;	
}		t_arg;

#endif
