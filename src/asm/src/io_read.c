/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:50:52 by cchen             #+#    #+#             */
/*   Updated: 2022/09/19 11:23:35 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	open_file(int *fd, const char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == ERROR)
		exit_error();
}

static off_t	file_size(int fd)
{
	off_t	start;
	off_t	size;
	off_t	res;

	start = lseek(fd, 0, SEEK_CUR);
	size = lseek(fd, 0, SEEK_END);
	res = lseek(fd, start, SEEK_SET);
	if (start == ERROR || size == ERROR || res == ERROR)
	{
		close(fd);
		exit_error();
	}
	return (size);
}

static void	init_buffer(const int fd, char **buffer, size_t	*size_ptr)
{
	size_t	size;

	size = (size_t) file_size(fd);
	if (!size)
		exit_error_str(ERR_MSG_EMPTY_FILE);
	*buffer = ft_memalloc(sizeof(**buffer) * size);
	if (!*buffer)
		exit_error();
	*size_ptr = size;
}

static long	read_file(const int fd, char *buffer, size_t size)
{
	return (read(fd, buffer, size));
}

char	*io_read(const char *filename)
{
	int		fd;
	size_t	size;
	char	*buffer;

	open_file(&fd, filename);
	init_buffer(fd, &buffer, &size);
	read_file(fd, buffer, size);
	close(fd);
	return (buffer);
}
