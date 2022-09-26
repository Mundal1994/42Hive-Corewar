/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:08:01 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 11:08:02 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_getsym(t_lexer *lexer, t_symbols *sym)
{
	t_source	*source;

	sym->num = 0;
	source = &lexer->source;
	source_seekstart(source);
}
