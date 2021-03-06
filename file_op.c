/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:31:25 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 01:57:06 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

ssize_t	getfilesize(char *filename)
{
	int		fd;
	ssize_t	size;
	int		r;
	char	buf;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	size = 0;
	while ((r = read(fd, &buf, 1)) == 1)
		size++;
	close(fd);
	if (r == 0)
		return (size);
	else
		return (-1);
}

void	*getfilecontents(char *filename, size_t *size)
{
	ssize_t			r;
	int				fd;
	unsigned char	*mem;

	if ((int)(*size = getfilesize(filename)) == -1)
		quit(errno, NULL);
	if ((mem = ft_memalloc(*size + 1)) == NULL)
		quit(errno, NULL);
	if ((fd = open(filename, O_RDONLY)))
	{
		r = read(fd, mem, *size);
		close(fd);
		if (r == (ssize_t)*size)
			return (mem);
	}
	free(mem);
	quit(errno, NULL);
	return (NULL);
}

void	putfilecontents(char *filename, t_uc *data, size_t size)
{
	int		fd;

	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		quit(errno, data);
	if ((write(fd, data, size)) == -1)
	{
		close(fd);
		quit(errno, data);
	}
	close(fd);
}
