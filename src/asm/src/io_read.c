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

static void	init_buffer(const int fd, t_vec *buffer)
{
	size_t	size;

	size = (size_t) file_size(fd);
	if (!size)
		exit_error_str(ERR_MSG_EMPTY_FILE);
	if (vec_new(buffer, ++size, sizeof(char)) == ERROR)
		exit_error();
}

static void	read_file(const int fd, t_vec *buffer)
{
	ssize_t	res;

	while (buffer->len < buffer->alloc_size)
	{
		res = read(fd, buffer->memory, buffer->alloc_size);
		if (res == ERROR)
			exit_error();
		if (!res)
			break ;
		buffer->len += (size_t) res;
	}
	vec_push(buffer, "\0");
}

void	io_read(const char *filename, t_vec *buffer)
{
	int		fd;

	open_file(&fd, filename);
	init_buffer(fd, buffer);
	read_file(fd, buffer);
	close(fd);
}
