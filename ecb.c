/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:17:29 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/17 21:30:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
//#include "../ft_printf/libftprintf.h"
#include <stdio.h>

int ecb()
{
	unsigned long m = 0x0123456789ABCDEF;
	unsigned long m_ip;
	unsigned long k = 0x133457799BBCDFF1;
	unsigned long keys[16];
	unsigned long er0;
	unsigned long sb0;
	unsigned long pp0;
	t_ul	l0;
	t_ul	r0;
	t_ul	r1;
	t_ul	result;
	int	i;

	make_keys(keys, k, 0);
//	ft_printf("message is %064lb\n", m);
	m_ip = make_ip1(m);
//	ft_printf("  after ip %064lb\n", m_ip);

	l0 = (m_ip >> 32) & 0xffffffff;
	r0 = m_ip & 0xffffffff;

	i = 0;
	while (i < 16)
	{
		er0 = make_ebit(r0); //expand r0 to 48 bits
		sb0 = get_s_boxes_value(er0 ^ keys[i]);       //back to 32 bits using s-boxes
		pp0 = make_pperm(sb0); //end of f-function
		r1 = l0 ^ pp0;
		l0 = r0;
		r0 = r1;
		i++;
	}
	result = (r1 << 32) + l0;
	result = make_ip2(result);
//	ft_printf("result   is: %064lb\n", result);
	printf("HEX is: %lX\n", result);
	return (0);

}
