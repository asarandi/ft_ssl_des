/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:20:45 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 02:41:22 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	quit(int errnum, void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr(strerror(errnum));
	ft_putstr("\n");
	exit(EXIT_FAILURE);
}

int		list_commands(int ac, char **av)
{
	int	x;

	x = ac - 1;
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

int		parse_commands(int ac, char **av)
{
	char *cmd;

	cmd = av[1];
	if (ft_strequ(cmd, "base64"))
		cmd_base64(ac, av);
	else if (ft_strequ(cmd, "des-ecb"))
		return (cmd_ecb(ac, av));
	else if (ft_strequ(cmd, "des-cbc"))
		return (cmd_cbc(ac, av));
	else if (ft_strequ(cmd, "des"))
		return (cmd_ecb(ac, av));
	else
		return (list_commands(ac, av));
	return (0);
}

int		main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr("usage: ");
		ft_putstr(av[0]);
		ft_putstr(" command [command opts] [command args]\n");
		return (64);
	}
	return (parse_commands(ac, av));
}
