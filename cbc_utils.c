/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 02:37:41 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 14:44:22 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	cbc_hex_iv_invalid_format(void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr("non-hex digit\ninvalid hex iv value\n");
	exit(0);
}

t_ul	cbc_get_iv(t_cmd *opt)
{
	unsigned char	*str_iv;
	unsigned long	size;

	if ((*opt).iv == NULL)
	{
		ft_putstr("enter initial vector: ");
		str_iv = stdin_read_line(&size);
		if (is_valid_hex_key(str_iv))
		{
			(*opt).master_iv = hex_to_ul64(str_iv);
			free(str_iv);
			return ((*opt).master_iv);
		}
		else
			cbc_hex_iv_invalid_format(str_iv);
	}
	else
	{
		if (is_valid_hex_key((unsigned char *)(*opt).iv))
			return (hex_to_ul64((unsigned char *)(*opt).iv));
		else
			cbc_hex_iv_invalid_format(NULL);
	}
	return (0);
}

void	cbc_print_key(t_cmd opt)
{
	ft_putstr("key=");
	ul64hex_to_stdout(opt.master_key);
	ft_putstr("\n");
	ft_putstr("iv =");
	ul64hex_to_stdout(opt.master_iv);
	ft_putstr("\n");
}

void	cbc_encrypt_input(t_cmd *opt, t_uc **input, t_uc **output, size_t *size)
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
		(*input)[(*size)++] = pad_byte;
	cbc_encrypt(input, *size, opt, DES_ENCRYPT);
	if ((*opt).b64 == 1)
	{
		*output = base64encode(*input, size);
		free(*input);
	}
	else
		*output = *input;
}

void	cbc_decrypt_input(t_cmd *opt, t_uc **input, t_uc **output, size_t *size)
{
	unsigned char	pad_byte;
	size_t			new_size;

	if ((*opt).b64 == 1)
	{
		*output = base64decode(*input, size);
		free(*input);
		*input = *output;
	}
	cbc_decrypt(input, *size, opt, DES_DECRYPT);
	pad_byte = (*input)[(*size) - 1];
	if ((pad_byte >= 1) && (pad_byte <= 8))
	{
		new_size = *size - pad_byte;
		while (((*input)[new_size] == pad_byte) && (new_size < *size))
			new_size++;
		if (new_size == *size)
			(*size) -= pad_byte;
	}
	*output = *input;
}
