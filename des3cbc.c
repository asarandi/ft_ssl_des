/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:16:09 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 16:14:03 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des3cbc_encrypt(t_uc **input, size_t size, t_cmd *opt)
{
	unsigned long	keys_1[16];
	unsigned long	keys_2[16];
	unsigned long	keys_3[16];
	unsigned long	data;
	size_t			i;

	make_keys(keys_1, (*opt).des3_key1, DES_ENCRYPT);
	make_keys(keys_2, (*opt).des3_key2, DES_DECRYPT);
	make_keys(keys_3, (*opt).des3_key3, DES_ENCRYPT);
	i = 0;
	while (i < size)
	{
		data = ecb_get_eight_bytes((*input) + i);
		data ^= (*opt).master_iv;
		data = ecb_process_block(data, keys_1);
		data = ecb_process_block(data, keys_2);
		data = ecb_process_block(data, keys_3);
		(*opt).master_iv = data;
		ecb_put_eight_bytes((*input) + i, data);
		i += 8;
	}
}

void	des3cbc_decrypt(t_uc **input, size_t size, t_cmd *opt, t_ul next_iv)
{
	unsigned long	keys_1[16];
	unsigned long	keys_2[16];
	unsigned long	keys_3[16];
	unsigned long	data;
	size_t			i;

	make_keys(keys_1, (*opt).des3_key3, DES_DECRYPT);
	make_keys(keys_2, (*opt).des3_key2, DES_ENCRYPT);
	make_keys(keys_3, (*opt).des3_key1, DES_DECRYPT);
	i = 0;
	while (i < size)
	{
		data = ecb_get_eight_bytes((*input) + i);
		next_iv = data;
		data = ecb_process_block(data, keys_1);
		data = ecb_process_block(data, keys_2);
		data = ecb_process_block(data, keys_3);
		data ^= (*opt).master_iv;
		(*opt).master_iv = next_iv;
		ecb_put_eight_bytes((*input) + i, data);
		i += 8;
	}
}

void	des3cbc_encrypt_input(t_cmd *opt, t_uc **in, t_uc **out, size_t *sz)
{
	unsigned char	*padded;
	size_t			new_size;
	unsigned char	pad_byte;

	new_size = ((*sz / 8) + 1) * 8;
	pad_byte = new_size - *sz;
	if ((padded = ft_memalloc(new_size + 1)) == NULL)
		quit(errno, *in);
	ft_memcpy(padded, *in, *sz);
	free(*in);
	*in = padded;
	while (*sz < new_size)
		(*in)[(*sz)++] = pad_byte;
	des3cbc_encrypt(in, *sz, opt);
	if ((*opt).b64 == 1)
	{
		*out = base64encode(*in, sz);
		free(*in);
	}
	else
		*out = *in;
}

void	des3cbc_decrypt_input(t_cmd *opt, t_uc **in, t_uc **out, size_t *sz)
{
	unsigned char	pad_byte;
	size_t			new_size;

	if ((*opt).b64 == 1)
	{
		*out = base64decode(*in, sz);
		free(*in);
		*in = *out;
	}
	des3cbc_decrypt(in, *sz, opt, 0);
	pad_byte = (*in)[(*sz) - 1];
	if ((pad_byte >= 1) && (pad_byte <= 8))
	{
		new_size = *sz - pad_byte;
		while (((*in)[new_size] == pad_byte) && (new_size < *sz))
			new_size++;
		if (new_size == *sz)
			(*sz) -= pad_byte;
	}
	*out = *in;
}
