/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caruychen <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:49:48 by caruychen         #+#    #+#             */
/*   Updated: 2022/09/25 22:22:55 by caruychen        ###   ########.fr       */
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

static void	init_buffer(const int fd, t_string *buffer)
{
	size_t	size;

	size = (size_t) file_size(fd);
	if (!size)
		exit_error_str(ERR_MSG_EMPTY_FILE);
	if (!string_new(buffer, size))
		exit_error();
}

static void	read_file(const int fd, t_string *buffer)
{
	ssize_t	res;

	while (buffer->length < buffer->capacity - 1)
	{
		res = read(fd, buffer->memory, buffer->capacity - 1);
		if (res == ERROR)
		{
			string_free(buffer);
			exit_error();
		}
		if (!res)
			break ;
		buffer->length += (size_t) res;
	}
}

void	source_read(t_source *source, const char *filename)
{
	int		fd;

	open_file(&fd, filename);
	init_buffer(fd, &source->buffer);
	read_file(fd, &source->buffer);
	close(fd);
}
