/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_push_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:56:35 by cchen             #+#    #+#             */
/*   Updated: 2022/10/05 15:56:36 by cchen            ###   ########.fr       */
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

static t_string	*push_num(t_string *buffer, uint32_t num, uint8_t size)
{
	char	byte;

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

t_string	*assemble_push_num(t_string *buffer, t_arg arg, uint8_t size)
{
	uint32_t	num;

	if (size != 1 && size != 2 && size != 4)
		return (NULL);
	if (size == 1)
		num = (uint32_t) arg.reg;
	if (size == 2)
		num = (uint32_t) arg.ind;
	if (size == 4)
		num = arg.dir;
	return (push_num(buffer, num, size));
}

t_string	*assemble_push_int(t_string *buffer, uint32_t num)
{
	return (push_num(buffer, num, 4));
}
