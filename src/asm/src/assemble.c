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

#include "asm.h"

int	assemble(t_lexer *lexer)
{
	t_parser	parser;

	parse_init(&parser, lexer);
	parse(&parser, lexer);
	parse_free(&parser);
	return (OK);
}
