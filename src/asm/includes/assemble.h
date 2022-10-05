/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:52:13 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 15:56:02 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLE_H
# define ASSEMBLE_H

# define BITS	8

typedef struct	s_assembler
{
	t_string	filename;	
	t_string	buffer;
}				t_assembler;

void		assemble_free(t_assembler *assembler, t_parser *parser);
void		assemble(const char *arg);
void		assemble_buffer(t_assembler *assembler, t_parser *parser);
t_string	*assemble_push_int(t_string *buffer, uint32_t num);
t_string	*assemble_push_num(t_string *buffer, t_arg arg, uint8_t size);

#endif
