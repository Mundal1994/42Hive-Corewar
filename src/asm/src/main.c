/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:16:33 by caruychen         #+#    #+#             */
/*   Updated: 2022/10/17 10:16:12 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "validator.h"
#include "assemble.h"

/*
 * 2 Primary stages of the assembler:
 * 1. Parse
 *   - Single pass
 *   - Performs all lexical and syntax analysis on code.
 *   - Returns a vector of 'statements' via the parser struct (t_header, t_body).
 *   - Statements are a struct containing the op code, acb, arguments &
 *     position in bytes.
 * 2. Assemble
 *   - Statement vector is unpacked into bytecode, and loaded into a buffer.
 *   - Once all statements are unpacked, the buffer is finally written to
 *     the resulting binary file.
 *
 * The Parse stage involves multiple phases of input processing:
 * 1. Source handling
 * 2. Lexical analysis
 * 3. Syntax analysis
 *   - Symbol table handling
 * More details for the parsing staged outlined in parse.c
*/
int	main(int argc, char **argv)
{
	t_parser	parser;

	validate_arguments(argc, argv);
	parse(&parser, argv[1]);
	assemble(&parser, argv[1]);
	return (EXIT_SUCCESS);
}
