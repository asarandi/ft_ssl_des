/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:41:36 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 14:47:35 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	get_triple_key(unsigned char *str_key, t_cmd *opt)
{
	if ((ft_strlen((char *)str_key)) > 32)
		(*opt).des3_key3 = hex_to_ul64(&str_key[32]);
	if ((ft_strlen((char *)str_key)) > 16)
		(*opt).des3_key2 = hex_to_ul64(&str_key[16]);
	if ((ft_strlen((char *)str_key)) > 0)
		(*opt).des3_key1 = hex_to_ul64(str_key);
}

void	des3_get_key(t_cmd *opt)
{
	unsigned char	*str_key;
	unsigned long	size;

	if ((*opt).key == NULL)
	{
		ft_putstr("enter des key in hex: ");
		str_key = stdin_read_line(&size);
		if (is_valid_hex_key(str_key))
		{
			get_triple_key(str_key, opt);
			free(str_key);
			return ;
		}
		else
			ecb_hex_key_invalid_format(str_key);
	}
	else
	{
		if (is_valid_hex_key((unsigned char *)(*opt).key))
			return (get_triple_key((unsigned char *)(*opt).key, opt));
		else
			ecb_hex_key_invalid_format(NULL);
	}
}

void	des3_print_key(t_cmd *opt, int print_iv)
{
	ft_putstr("key=");
	ul64hex_to_stdout((*opt).des3_key1);
	ul64hex_to_stdout((*opt).des3_key2);
	ul64hex_to_stdout((*opt).des3_key3);
	ft_putstr("\n");
	if (print_iv == 1)
	{
		ft_putstr("iv =");
		ul64hex_to_stdout((*opt).master_iv);
		ft_putstr("\n");
	}
}

void	cmd_des3cbc(int ac, char **av)
{
	unsigned char	*input;
	unsigned char	*output;
	size_t			size;
	t_cmd			opt;

	get_options(2, ac, av, &opt);
	des3_get_key(&opt);
	opt.master_iv = cbc_get_iv(&opt);
	if (opt.print == 1)
		des3_print_key(&opt, 1);
	get_input(&opt, &input, &size);
	if (opt.dec == 1)
		des3cbc_decrypt_input(&opt, &input, &output, &size);
	else
		des3cbc_encrypt_input(&opt, &input, &output, &size);
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output, "-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);
}

void	cmd_des3ecb(int ac, char **av)
{
	unsigned char	*input;
	unsigned char	*output;
	size_t			size;
	t_cmd			opt;

	get_options(2, ac, av, &opt);
	des3_get_key(&opt);
	if (opt.print == 1)
		des3_print_key(&opt, 0);
	get_input(&opt, &input, &size);
	if (opt.dec == 1)
		des3ecb_decrypt_input(&opt, &input, &output, &size);
	else
		des3ecb_encrypt_input(&opt, &input, &output, &size);
	if ((opt.output == NULL) || ((opt.output) && (ft_strequ(opt.output, "-"))))
		write(1, output, size);
	else
		putfilecontents(opt.output, output, size);
	free(output);
}
