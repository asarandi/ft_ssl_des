/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 02:27:37 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 02:27:49 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_options(t_cmd *opt)
{
	(*opt).enc = 0;
	(*opt).dec = 0;
	(*opt).b64 = 0;
	(*opt).print = 0;
	(*opt).master_key = 0;
	(*opt).key = NULL;
	(*opt).iv = NULL;
	(*opt).input = NULL;
	(*opt).output = NULL;
}

void	show_options(char *s)
{
	ft_putstr("unknown option '");
	ft_putstr(s);
	ft_putstr("'\noptions are\n");
	ft_putstr("-i <file>      input file\n");
	ft_putstr("-o <file>      output file\n");
	ft_putstr("-e             encrypt\n");
	ft_putstr("-d             decrypt\n");
	ft_putstr("-a             base64 encode/decode\n");
	ft_putstr("-k             key in hex is the next argument\n");
	ft_putstr("-v             iv in hex is the next argument\n");
	ft_putstr("-p             print the iv/key\n");
	exit(0);
}

void	get_options(int i, int ac, char **av, t_cmd *opt)
{
	init_options(opt);
	while (i < ac)
	{
		if (ft_strequ(av[i], "-e"))
			(*opt).enc = 1;
		else if (ft_strequ(av[i], "-d"))
			(*opt).dec = 1;
		else if (ft_strequ(av[i], "-a"))
			(*opt).b64 = 1;
		else if (ft_strequ(av[i], "-p"))
			(*opt).print = 1;
		else if ((ft_strequ(av[i], "-i")) && (av[i + 1]))
			(*opt).input = av[++i];
		else if ((ft_strequ(av[i], "-o")) && (av[i + 1]))
			(*opt).output = av[++i];
		else if ((ft_strequ(av[i], "-k")) && (av[i + 1]))
			(*opt).key = av[++i];
		else if ((ft_strequ(av[i], "-v")) && (av[i + 1]))
			(*opt).iv = av[++i];
		else
			show_options(av[i]);
		i++;
	}
}
