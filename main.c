/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:20:45 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/18 01:48:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_options(t_cmd *opt)
{
	(*opt).enc = 0;
	(*opt).dec = 0;
	(*opt).b64 = 0;
	(*opt).key = NULL;
	(*opt).iv = NULL;
	(*opt).input = NULL;
	(*opt).output = NULL;
}

void	quit(int errnum, void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr(strerror(errnum));
	ft_putstr("\n");
	exit(EXIT_FAILURE);
}

unsigned char	*read_stdin(size_t *count)
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
	exit(0);
}

void	get_options(int ac, char **av, t_cmd *opt)
{
	int		i;

	init_options(opt);
	i = 2;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-e"))
			(*opt).enc = 1;
		else if (ft_strequ(av[i], "-d"))
			(*opt).dec = 1;
		else if (ft_strequ(av[i], "-a"))
			(*opt).b64 = 1;
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

void get_input(t_cmd *opt, unsigned char **input, size_t *size)
{
	if (((*opt).input == NULL) || 
			(((*opt).input) && (ft_strequ((*opt).input,"-"))))
		*input = read_stdin(size);
	else
		*input = getfilecontents((*opt).input, size);
}

int	cmd_cbc(int ac, char **av)
{
	return (0);
}


unsigned long	ecb_read_password()
{
	unsigned char	*pw1;
	unsigned char	*pw2;
	unsigned long	mk1;
	unsigned long	mk2;

	pw1 = read_stdin(&mk1);//getpass("enter des-ecb encryption password:");
	mk1 = text_to_ul64((char *)pw1);
	pw2 = read_stdin(&mk2);//getpass("Verifying - enter des-ecb encryption password:");
	mk2 = text_to_ul64((char *)pw2);
	if (mk1 == mk2)
	{
		return(mk1);
	}
	ft_putstr("Verify failure\nbad password read\n");
	exit(0);
	return (0);
}

unsigned long	ecb_process_key(t_cmd *opt)
{
	return (0);
}


int	cmd_ecb(int ac, char **av)
{
	unsigned long	master_key;
	t_cmd			opt;

	get_options(ac, av, &opt);
	
	if (opt.key == NULL)
		master_key = ecb_read_password();
	else
		master_key = ecb_process_key(&opt);





	return (0);
}

void	cmd_base64(int ac, char **av)
{
	size_t			size;
	unsigned char	*input;
	unsigned char	*output;
	t_cmd			opt;

	get_options(ac, av, &opt);
	get_input(&opt, &input, &size);
	if (opt.dec == 1)
		output = base64decode(input, &size);
	else
		output = base64encode(input, &size);
	free(input);
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output,"-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);

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
		cmd_base64(ac, av);
	else if (ft_strequ(cmd, "des-ecb"))
		return(cmd_ecb(ac, av));
	else if (ft_strequ(cmd, "des-cbc"))
		return(cmd_cbc(ac, av));
	else if (ft_strequ(cmd, "des"))
		return(cmd_ecb(ac, av));
	else
		return(list_commands(ac, av));
	return (0);
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
