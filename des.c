/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:55:34 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/17 21:18:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long	make_ip1(unsigned long m)
{
	unsigned long	result;
	int				i;

	i = 0;
	result = 0;
	while (i < 64)
	{
		result <<= 1;
		result += (m >> (64 - g_ip1_table[i])) & 1;
		i++;
	}
	return (result);
}

unsigned long	make_ebit(unsigned long r0)
{
	unsigned long	result;
	unsigned long	tmp;
	int				i;

	i = 0;
	result = 0;
	while (i < 48)
	{
		tmp = (r0 >> (32 - g_ebit_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}

unsigned long	get_s_boxes_value(unsigned long xor0)
{
	int		i;
	int		row;
	int		col;
	t_ul	tmp;
	t_ul	result;

	i = 0;
	result = 0;
	while (i < 8)
	{
		tmp = (xor0 >> (42 - (i * 6))) & 0x3f;
		row = ((tmp >> 5) << 1) + (tmp & 1);
		col = (tmp >> 1) & 0xf;
		tmp = g_s_boxes[i][row * 16 + col];
		result <<= 4;
		result += tmp;
		i++;
	}
	return (result);
}

unsigned long	make_pperm(unsigned long sb0)
{
	int				i;
	unsigned long	tmp;
	unsigned long	result;

	i = 0;
	result = 0;
	while (i < 32)
	{
		tmp = (sb0 >> (32 - g_pperm_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}

unsigned long	make_ip2(unsigned long rxlx)
{
	int				i;
	unsigned long	tmp;
	unsigned long	result;

	i = 0;
	result = 0;
	while (i < 64)
	{
		tmp = (rxlx >> (64 - g_ip2_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}
