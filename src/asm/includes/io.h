/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:01:35 by cchen             #+#    #+#             */
/*   Updated: 2022/09/19 10:09:44 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char	*io_read(const char *filename);

#endif
