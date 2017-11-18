/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:16:02 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/17 20:46:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long	make_pc1(unsigned long k)
{
	unsigned long	result;
	unsigned long	tmp;
	int				i;

	result = 0;
	i = 0;
	while (i < 56)
	{
		tmp = (k >> (64 - g_pc1_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	result <<= 8;
	return (result);
}

unsigned long	circular_shift_left(unsigned long key, int bits)
{
	unsigned long	result;
	unsigned long	tmp;
	unsigned long	fullbits;

	tmp = bits;
	fullbits = 0;
	while (tmp--)
		fullbits = (fullbits << 1) + 1;
	tmp = (key >> (bits - 1)) & 1;
	result = ((key << 1) + tmp) & fullbits;
	return (result);
}

void			make_half_keys(unsigned long half_keys[16], t_ul starter)
{
	unsigned char	shift;
	unsigned long	new_half;
	int				i;

	i = 0;
	while (i < 16)
	{
		shift = g_left_shifts[i];
		while (shift--)
		{
			new_half = circular_shift_left(starter, 28);
			starter = new_half;
		}
		half_keys[i] = new_half;
		i++;
	}
}

unsigned long	make_pc2(unsigned long c_half, unsigned long d_half)
{
	t_ul	before;
	t_ul	after;
	int		i;

	before = (c_half << 28) + d_half;
	i = 0;
	after = 0;
	while (i < 48)
	{
		after <<= 1;
		after += ((before >> (56 - g_pc2_table[i])) & 1);
		i++;
	}
	return (after);
}

void			make_keys(unsigned long keys[16], t_ul master_key, int rev)
{
	unsigned long	kp;
	unsigned long	c_half_keys[16];
	unsigned long	d_half_keys[16];
	int				i;

	kp = make_pc1(master_key);
	make_half_keys(c_half_keys, (kp >> 36) & 0xfffffff);
	make_half_keys(d_half_keys, (kp >> 8) & 0xfffffff);
	i = 0;
	while (i < 16)
	{
		kp = i;
		if (rev == 1)
			kp = 15 - i;
		keys[kp] = make_pc2(c_half_keys[i], d_half_keys[i]);
		i++;
	}
}
