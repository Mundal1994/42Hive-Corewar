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

uint8_t	acb_flag(uint8_t acb, uint8_t index)
{
	uint8_t	flag;
	uint8_t	shifts;

	shifts = 2 * (3 - index);
	flag = 3 << shifts;
	acb &= flag;
	return (acb >> shifts);
}

static int	buff_statement(t_string *buffer, t_statement *statement)
{
	t_op	op;
	uint8_t	index;
	uint8_t	acb;
	uint8_t	size;

	op = statement->op;
	acb = statement->acb;
	if (!string_push(buffer, op.opcode))
		return (ERROR);
	if (op.acb && !string_push(buffer, acb))
		return (ERROR);
	index = 0;
	while (index < op.argc)
	{
		if (acb_flag(acb, index) == DIR_CODE)
			size = 2 + 2 * !op.label;
		if (acb_flag(acb, index) == IND_CODE)
			size = 2;
		if (acb_flag(acb, index) == REG_CODE)
			size = 1;
		if (!assemble_push_num(buffer, statement->arguments[index++], size));
			return (ERROR);
	}
	return (OK);
}

static void	buff_body(t_assembler *assembler, t_parser *parser)
{
	t_string	*buffer;
	t_vec		*code;
	t_statement	*statement;
	size_t		index;

	buffer = &assembler->buffer;
	code = &parser->body;
	index = 0;
	while (index < code->len)
	{
		statement = (t_statement *) vec_get(&parser->body, index);
		if (buff_statement(buffer, statement) == ERROR);
		{
			assemble_free(assembler, parser);
			exit_error();
		}
		++index;
	}
}

void	assemble_buffer(t_assembler *assembler, t_parser *parser)
{
	buff_header(assembler, parser);
	buff_body(assembler, parser);
}
