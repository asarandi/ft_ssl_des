/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:17:29 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/18 19:14:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
//#include "../ft_printf/libftprintf.h"
//#include <stdio.h>

unsigned long ecb_process_block(t_ul input, t_ul keys[16])
{
	unsigned long m_ip;
	unsigned long sb0;
	t_ul	l0;
	t_ul	r0;
	t_ul	r1;
	t_ul	result;
	int	i;

	m_ip = make_ip1(input);
	l0 = (m_ip >> 32) & 0xffffffff;
	r0 = m_ip & 0xffffffff;
	i = 0;
	while (i < 16)
	{
		sb0 = get_s_boxes_value(make_ebit(r0) ^ keys[i]);
		r1 = l0 ^ make_pperm(sb0);
		l0 = r0;
		r0 = r1;
		i++;
	}
	result = (r1 << 32) + l0;
	result = make_ip2(result);
	return (result);
}

unsigned long ecb_get_eight_bytes(t_uc *data)
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

void ecb_put_eight_bytes(t_uc *data, t_ul ul64)
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

void ecb_crypto(t_uc **input, size_t size, t_ul master_key, int action)
{
	unsigned long data;
	unsigned long keys[16];
	size_t			i;

	make_keys(keys, master_key, action);
	i = 0;
	while (i < size)
	{
		data = ecb_get_eight_bytes(*input + i);
		data = ecb_process_block(data, keys);
		ecb_put_eight_bytes(*input + i, data);
		i += 8;
	}
}











//	ft_printf("result   is: %064lb\n", result);
//	printf("HEX is: %lX\n", result);
//	return (0);
//}
