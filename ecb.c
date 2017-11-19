/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:17:29 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 01:55:19 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long	ecb_process_block(t_ul input, t_ul keys[16])
{
	unsigned long	norme;
	unsigned long	left0;
	unsigned long	right0;
	unsigned long	right1;
	int				i;

	norme = make_ip1(input);
	left0 = (norme >> 32) & 0xffffffff;
	right0 = norme & 0xffffffff;
	i = 0;
	while (i < 16)
	{
		norme = get_s_boxes_value(make_ebit(right0) ^ keys[i]);
		right1 = left0 ^ make_pperm(norme);
		left0 = right0;
		right0 = right1;
		i++;
	}
	return (make_ip2((right1 << 32) + left0));
}

unsigned long	ecb_get_eight_bytes(unsigned char *data)
{
	unsigned long	result;
	int				i;

	i = 0;
	result = 0;
	while (i < 8)
	{
		result <<= 8;
		result += data[i];
		i++;
	}
	return (result);
}

void			ecb_put_eight_bytes(unsigned char *data, t_ul ul64)
{
	unsigned char	c;
	int				i;

	i = 0;
	while (i < 8)
	{
		c = (ul64 >> (56 - (i * 8))) & 0xff;
		data[i] = c;
		i++;
	}
}

void			ecb_crypto(t_uc **input, size_t size, t_ul mk, int enc)
{
	unsigned long	data;
	unsigned long	keys[16];
	size_t			i;

	make_keys(keys, mk, enc);
	i = 0;
	while (i < size)
	{
		data = ecb_get_eight_bytes(*input + i);
		data = ecb_process_block(data, keys);
		ecb_put_eight_bytes(*input + i, data);
		i += 8;
	}
}
