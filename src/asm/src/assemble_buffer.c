/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:40:04 by cchen             #+#    #+#             */
/*   Updated: 2022/10/05 14:40:05 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_string	*push_null(t_string *buffer)
{
	if (!buffer || !buffer->capacity)
		return (NULL);
	if (buffer->length >= buffer->capacity - 1)
		if (!string_resize(buffer, buffer->capacity * STR_RESIZE_FACTOR))
			return (NULL);
	++buffer->length;
	return (buffer);
}

t_string	*assemble_push_int(t_string *buffer, uint32_t num)
{
	size_t	size;
	char	byte;

	size = 4;
	while (size > 0)
	{
		byte = num >> (BITS * --size);
		if (byte == 0)
		{
			if (!push_null(buffer))
				return (NULL);
			continue ;
		}
		if (!string_push(buffer, byte))
			return (NULL);
	}
	return (buffer);
}

static void buff_header(t_assembler *assembler, t_parser *parser)
{
	t_string	*buffer;

	buffer = &assembler->buffer;
	if (assemble_push_int(buffer, (uint32_t) parser->header.magic)
		&& string_concat_n(buffer, parser->header.prog_name, PROG_NAME_LENGTH)
		&& assemble_push_int(buffer, (uint32_t) 0)
		&& assemble_push_int(buffer, parser->size)
		&& string_concat_n(buffer, parser->header.comment, COMMENT_LENGTH)
		&& assemble_push_int(buffer, (uint32_t) 0))
		return ;
	assemble_free(assembler, parser);
	exit_error();
}

void	assemble_buffer(t_assembler *assembler, t_parser *parser)
{
	buff_header(assembler, parser);
	buff_body(t_assembler *assembler, t_parser *parser);
}
