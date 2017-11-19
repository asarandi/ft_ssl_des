/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:20:45 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/18 20:08:25 by asarandi         ###   ########.fr       */
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

void	quit(int errnum, void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr(strerror(errnum));
	ft_putstr("\n");
	exit(EXIT_FAILURE);
}

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

void get_input(t_cmd *opt, unsigned char **input, size_t *size)
{
	if (((*opt).input == NULL) || 
			(((*opt).input) && (ft_strequ((*opt).input,"-"))))
		*input = stdin_read_eof(size);
	else
		*input = getfilecontents((*opt).input, size);
}

int	cmd_cbc(int ac, char **av)
{
	return (0);
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



void	ecb_hex_key_invalid_format(void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr("non-hex digit\ninvalid hex key value\n");
	exit(0);
}

/*
**  the subject is asking to pad short keys with same digits,
**  so key '123' becomes 0x1230123012301230
**  the key 'ABCD' becomes 0xabcdabcdabcdabcd
**
**  in openssl a short key is padded with 0's
**  so key '123' in openssl would be 0x1230000000000000
**  and key 'ABCD' in openssl wouble be 0xabcd000000000000
**
**  to make the project compatible with openssl
**  change 'hex_to_ul64' to 'hex_to_ul64_openssl'
**
**  use the -p option to show the key being used
*/

unsigned long	ecb_get_key(t_cmd *opt)
{
	unsigned char	*str_key;
	unsigned long	size;

	if ((*opt).key == NULL)
	{
		ft_putstr("enter des key in hex: ");
		str_key = stdin_read_line(&size);
		if (is_valid_hex_key(str_key))
		{
			size = hex_to_ul64_openssl(str_key);
			free(str_key);
			return(size);
		}
		else
			ecb_hex_key_invalid_format(str_key);
	}
	else
	{
		if (is_valid_hex_key((unsigned char *)(*opt).key))
			return(hex_to_ul64_openssl((unsigned char *)(*opt).key));
		else
			ecb_hex_key_invalid_format(NULL);
	}
	return (0);
}

void	ecb_print_key(unsigned long master_key)
{
	ft_putstr("key=");
	ul64hex_to_stdout(master_key);
	ft_putstr("\n");
}


void ecb_process_input(t_cmd *opt, t_uc **input, t_uc **output, size_t *size)
{
	unsigned char	*padded;
	size_t			new_size;
	unsigned char	pad_byte;

	new_size = ((*size / 8) + 1) * 8;
	pad_byte = new_size - *size;
	if ((padded = ft_memalloc(new_size + 1)) == NULL)
		quit(errno, *input);
	ft_memcpy(padded, *input, *size);
	free(*input);
	*input = padded;
	while (*size < new_size)
		padded[(*size)++] = pad_byte;
	ecb_crypto(input, *size, (*opt).master_key, DES_ENCRYPT);
	*output = ft_memalloc(*size + 1);
	ft_memcpy(*output, *input, *size);

}


int	cmd_ecb(int ac, char **av)
{
	unsigned char	*input;
	unsigned char	*output;
	size_t			size;
	t_cmd			opt;

	get_options(2, ac, av, &opt);
	opt.master_key = ecb_get_key(&opt);
	if (opt.print == 1)
		ecb_print_key(opt.master_key);
	get_input(&opt, &input, &size);
	ecb_process_input(&opt, &input, &output, &size);
	free(input);
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output,"-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);
	return (0);
}

void	cmd_base64(int ac, char **av)
{
	unsigned char	*input;
	unsigned char	*output;
	size_t			size;
	t_cmd			opt;

	get_options(2, ac, av, &opt);
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
