/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:20:45 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/15 02:56:56 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define BUF_SIZE 1024

void	quit(int errnum, void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr(strerror(errnum));
	exit(EXIT_FAILURE);
}

unsigned char	*read_stdin(size_t *count)
{
	unsigned char	*buffer;
	unsigned char	*newbuf;
	size_t	r;

	if ((buffer = ft_memalloc(BUF_SIZE)) == NULL)
		quit(errno, NULL);
	*count = 0;
	r = BUF_SIZE;
	while (r != 0)
	{
		if ((r = read(STDIN_FILENO, &buffer[*count], BUF_SIZE)) == -1)
			quit(errno, buffer);
		*count += r;
		if (r == BUF_SIZE)
		{
			if ((newbuf = ft_memalloc(*count + BUF_SIZE)) == NULL)
				quit(errno, buffer);
			ft_memcpy(newbuf, buffer, *count);
			free(buffer);
			buffer = newbuf;
		}
	}
	return (buffer);
}

int	cmd_cbc(int ac, char **av)
{
	return (0);
}

int	cmd_ecb(int ac, char **av)
{
	return (0);
}

int	cmd_base64(int ac, char **av)
{
	size_t			size;
	unsigned char	*input;
	char			*output;

	input = read_stdin(&size);
	output = base64encode(input, size);
	free(input);
	ft_putstr(output);
	free(output);

	return (0);

}

int	list_commands(int ac, char **av)
{
	ft_putstr(av[0]);
	ft_putstr(": Error: '");
	ft_putstr(av[1]);
	ft_putstr("' is an invalid command.\n\n");
	ft_putstr("Standard commands:\n\n");
	ft_putstr("Message Digest commands:\n\n");
	ft_putstr("Cipher commands:\n");
	ft_putstr("base64\n");
	ft_putstr("des\n");
	ft_putstr("des-ecb\n");
	ft_putstr("des-cbc\n");
	return (64);
}

int	parse_command(int ac, char **av)
{
	char *cmd;

	cmd = av[1];
	if (ft_strequ(cmd, "base64"))
		return(cmd_base64(ac, av));
	else if (ft_strequ(cmd, "des-ecb"))
		return(cmd_ecb(ac, av));
	else if (ft_strequ(cmd, "des-cbc"))
		return(cmd_cbc(ac, av));
	else if (ft_strequ(cmd, "des"))
		return(cmd_cbc(ac, av));
	return(list_commands(ac, av));
}

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr("usage: ");
		ft_putstr(av[0]);
		ft_putstr(" command [command opts] [command args]\n");
		return (64);
	}
	return (parse_command(ac, av));
}
