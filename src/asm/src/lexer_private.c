/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_private.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:38:47 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 15:38:48 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	_lexer_getcmd(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	start = source->curr;
	len = 1;
	while (ft_isalnum(*source_next(source)))
		++len;
	string_replace_n(&sym->str, start, len);
};

void	_lexer_getword(t_source *source, t_symbols *sym)
{

}
