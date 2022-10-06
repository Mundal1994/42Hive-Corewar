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

static void	write_fiile(int fd, t_assembler *assembler)
{

}

void	assemble_wrte(t_assembler *assembler)
{
	int	fd;

	open_file(&fd, assembler);
	write_file(fd, assembler);
}
