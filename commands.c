/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 02:31:02 by asarandi          #+#    #+#             */
/*   Updated: 2018/12/26 10:54:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	get_input(t_cmd *opt, unsigned char **input, size_t *size)
{
	if (((*opt).input == NULL) ||
					(((*opt).input) && (ft_strequ((*opt).input, "-"))))
	{
		*input = stdin_read_eof(size);
	}
	else
		*input = getfilecontents((*opt).input, size);
	if (*size < 1)
	{
		ft_putstr("no input data\n");
		exit(0);
	}
}

void	cmd_cbc(int ac, char **av)
{
	unsigned char	*input;
	unsigned char	*output;
	size_t			size;
	t_cmd			opt;

	get_options(2, ac, av, &opt);
	opt.master_key = ecb_get_key(&opt);
	opt.master_iv = cbc_get_iv(&opt);
	if (opt.print == 1)
		cbc_print_key(opt);
	get_input(&opt, &input, &size);
	if (opt.dec == 1)
		cbc_decrypt_input(&opt, &input, &output, &size);
	else
		cbc_encrypt_input(&opt, &input, &output, &size);
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output, "-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);
}

void	cmd_ecb(int ac, char **av)
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
	if (opt.dec == 1)
		ecb_decrypt_input(&opt, &input, &output, &size);
	else
		ecb_encrypt_input(&opt, &input, &output, &size);
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output, "-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);
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
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output, "-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);
}
