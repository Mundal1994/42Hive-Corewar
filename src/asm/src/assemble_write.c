/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:35:35 by cchen             #+#    #+#             */
/*   Updated: 2022/10/06 09:35:36 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	open_file(int *fd, t_assembler *assembler)
{
	const char	*filename;

	filename = assembler->filename.memory;
	*fd = open(filename, O_WRONLY | O_TRUNC);
	if (*fd > ERROR)
		return ;
	assemble_free(assembler);
	exit_error();
}

static void	write_file(int fd, t_assembler *assembler)
{
	ssize_t		res;
	t_string	buffer;
	size_t		written;

	buffer = assembler->buffer;
	written = 0;
	while (written < buffer.length)
	{
		res = write(fd, buffer.memory + written, buffer.length - written);
		if (res == ERROR)
		{
			assemble_free(assembler);
			exit_error();
		}
		if (!res)
			break;
		written += (size_t) res;
	}
}

void	assemble_write(t_assembler *assembler)
{
	int	fd;

	open_file(&fd, assembler);
	write_file(fd, assembler);
	close(fd);
}
