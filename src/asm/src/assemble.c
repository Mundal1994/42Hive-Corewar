/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:53:37 by cchen             #+#    #+#             */
/*   Updated: 2022/09/29 16:00:52 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** *
 * Assembly expectes a successfully parsed source code.
 * Processes the unpacked instructions from parser->body, and follows the 
 * following stages:
 * 1. Initialise assembly buffer
 * 2. Loads bytecode into buffer memory
 * 3. Writes the buffer into file
 * ************************************************************************* */

#include "assemble.h"
#include "errors.h"
#include "ft_printf.h"

static void	assemble_init(t_assembler *assembler, t_parser *parser,
		const char *arg)
{
	size_t	len;
	size_t	cor_size;

	if (parser->size > CHAMP_MAX_SIZE)
	{
		warning_ret(ASM_WARN_LARGE_CHAMP);
		ft_printf("\tYour champion size: %ld bytes > %d bytes (CHAMP_MAX_SIZE)\n",
			parser->size,
			CHAMP_MAX_SIZE);
	}
	assembler->parser = parser;
	len = ft_strrchr(arg, '.') - arg + 1;
	cor_size = 8 + PROG_NAME_LENGTH + COMMENT_LENGTH + parser->size;
	if (!string_from_n(&assembler->filename, arg, len)
		|| !string_concat(&assembler->filename, "cor")
		|| !string_new(&assembler->buffer, cor_size))
	{
		assemble_free(assembler);
		exit_error();
	}
}

void	assemble_free(t_assembler *assembler)
{
	parse_free(assembler->parser);
	if (assembler->filename.capacity)
		string_free(&assembler->filename);
	if (assembler->buffer.capacity)
		string_free(&assembler->buffer);
}

/* Begins main assembly phase */
void	assemble(t_parser *parser, const char *arg)
{
	t_assembler	assembler;

	assemble_init(&assembler, parser, arg);
	assemble_buffer(&assembler);
	assemble_write(&assembler);
	assemble_free(&assembler);
}
