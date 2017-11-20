/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:46:09 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 23:54:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			cbc_encrypt(t_uc **input, size_t size, t_cmd *opt, int enc)
{
	unsigned long	data;
	unsigned long	keys[16];
	size_t			i;
	unsigned long	iv;

	make_keys(keys, (*opt).master_key, enc);
	i = 0;
	iv = (*opt).master_iv;
	while (i < size)
	{
		data = ecb_get_eight_bytes((*input) + i);
		data ^= iv;
		data = ecb_process_block(data, keys);
		iv = data;
		ecb_put_eight_bytes((*input) + i, data);
		i += 8;
	}
}

void			cbc_decrypt(t_uc **input, size_t size, t_cmd *opt, int enc)
{
	unsigned long	data;
	unsigned long	keys[16];
	size_t			i;
	unsigned long	iv;
	unsigned long	next_iv;

	make_keys(keys, (*opt).master_key, enc);
	i = 0;
	iv = (*opt).master_iv;
	while (i < size)
	{
		data = ecb_get_eight_bytes((*input) + i);
		next_iv = data;
		data = ecb_process_block(data, keys);
		data ^= iv;
		iv = next_iv;
		ecb_put_eight_bytes((*input) + i, data);
		i += 8;
	}
}
