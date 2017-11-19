/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 02:25:09 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 02:25:24 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*stdin_read_eof(size_t *count)
{
	unsigned char	*buffer;
	unsigned char	*newbuf;
	ssize_t			r;

	if ((buffer = ft_memalloc(BUF_SIZE)) == NULL)
		quit(errno, NULL);
	*count = 0;
	r = 1;
	while (r != 0)
	{
		if ((r = read(0, &buffer[*count], 1024 - (*count % 1024))) == -1)
			quit(errno, buffer);
		*count += r;
		if ((*count) && (*count % BUF_SIZE == 0))
		{
			if ((newbuf = ft_memalloc(*count + BUF_SIZE)) == NULL)
				quit(errno, buffer);
			ft_memcpy(newbuf, buffer, *count);
			free(buffer);
			buffer = newbuf;
			r = 1;
		}
	}
	return (buffer);
}

unsigned char	*stdin_read_line(size_t *count)
{
	unsigned char	*buffer;
	ssize_t			r;

	if ((buffer = ft_memalloc(128)) == NULL)
		quit(errno, NULL);
	*count = 0;
	r = 1;
	while (r != 0)
	{
		if ((r = read(0, &buffer[*count], 1)) == -1)
			quit(errno, buffer);
		if ((buffer[*count] == '\n') || (buffer[*count] == '\r'))
		{
			buffer[*count] = 0;
			break ;
		}
		*count += r;
		if (*count > 127)
			break ;
	}
	return (buffer);
}
