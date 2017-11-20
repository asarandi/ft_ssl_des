/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 02:37:41 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 00:27:57 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
**  to make the project compatible with subject.pdf
**  change 'hex_to_ul64_openssl' to 'hex_to_ul64'
**
**  use the -p option to show the key being used
*/

t_ul	ecb_get_key(t_cmd *opt)
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
			return (size);
		}
		else
			ecb_hex_key_invalid_format(str_key);
	}
	else
	{
		if (is_valid_hex_key((unsigned char *)(*opt).key))
			return (hex_to_ul64_openssl((unsigned char *)(*opt).key));
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

void	ecb_encrypt_input(t_cmd *opt, t_uc **input, t_uc **output, size_t *size)
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
	ecb_crypto(input, *size, (*opt).master_key, DES_ENCRYPT);
	if ((*opt).b64 == 1)
	{
		*output = base64encode(*input, size);
		free(*input);
	}
	else
		*output = *input;
}

void	ecb_decrypt_input(t_cmd *opt, t_uc **input, t_uc **output, size_t *size)
{
	unsigned char	pad_byte;
	size_t			new_size;

	if ((*opt).b64 == 1)
	{
		*output = base64decode(*input, size);
		free(*input);
		*input = *output;
	}
	ecb_crypto(input, *size, (*opt).master_key, DES_DECRYPT);
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
