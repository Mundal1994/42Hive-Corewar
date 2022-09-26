/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_private.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:38:47 by cchen             #+#    #+#             */
/*   Updated: 2022/09/26 23:06:10 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	is_wordch(char c)
{
	return (ft_islower(c) || ft_isdigit(c) || c == '_');
}

void	lexer_getcmd(t_source *source, t_symbols *sym)
{
	size_t	len;
	char	*start;

	sym.type = LA_cmd;
	start = source->curr;
	len = 1;
	while (ft_isalnum(*source_next(source)))
		++len;
	string_replace_n(&sym->str, start, len);
}

static int	set_label(t_source *source, t_symbols *sym, char *start,
		size_t len)
{
	string_replace_n(&sym->str, start, len);
	sym->type = LA_id;
	source_next(source);
	return (OK);
}

static int	set_num(t_symbols *sym)
{
	sym->type = LA_num;
	sym->num = ft_atoi(sym->str.buffer);
	if (sym->num < 0)
		return (ERROR);
	return (OK);
}

int	lexer_getword(t_source *source, t_symbols *sym)
{
	size_t	len;	
	char	*curr;
	char	*start;
	bool	isnumber;

	isnumber = true;
	curr = source->curr;
	start = source->curr;
	len = 0;
	while (curr && (is_wordch(*curr) || *curr == LABEL_CHAR))
	{
		if (*curr == LABEL_CHAR && sym->islabel)
			return (set_label(source, sym, start, len));
		if ((*curr == LABEL_CHAR || *curr == '_') && !sym->islabel)
			sym->type = LA_unknown;
		if (!ft_isdigit(*curr))
			isnumber = false;
		curr = source_next(source); 
		++len;
	}
	sym->islabel = false;
	string_replace_n(&sym->str, start, len);
	if (sym->type == LA_unknown)
		return (ERROR);
	if (isnumber)
		return (set_num(sym));
	return (sym->type = LA_id, OK);
}
