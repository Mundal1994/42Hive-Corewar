/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:00:57 by cchen             #+#    #+#             */
/*   Updated: 2022/09/19 11:01:14 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

void	exit_error(void);
void	exit_error_str(char *str);
int		error(char *msg);
int		syntax_error(char *msg, char *token, t_lexer lexer);

#endif
