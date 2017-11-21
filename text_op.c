/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 00:05:45 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 14:00:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				is_valid_hex_key(unsigned char *s)
{
	int	i;

	i = 0;
	s = ft_strtolower(s);
	while (s[i] != 0)
	{
		if ((s[i] >= '0') && (s[i] <= '9'))
			i++;
		else if ((s[i] >= 'a') && (s[i] <= 'f'))
			i++;
		else
			return (0);
	}
	return (1);
}

unsigned long	text_to_ul64(unsigned char *s)
{
	int				i;
	int				j;
	unsigned long	result;
	unsigned char	c;

	i = 0;
	j = 0;
	result = 0;
	while (i < 8)
	{
		if (!s[j])
			j = 0;
		c = s[j++];
		result <<= 8;
		result += c;
		i++;
	}
	return (result);
}

unsigned long	hex_to_ul64(unsigned char *s)
{
	int				i;
	int				j;
	unsigned long	result;
	unsigned char	c;

	s = ft_strtolower(s);
	i = 0;
	j = 0;
	result = 0;
	while (i < 16)
	{
		c = s[j];
		if (s[j])
			j++;
		result <<= 4;
		if ((c >= '0') && (c <= '9'))
			result += (c - '0');
		if ((c >= 'a') && (c <= 'f'))
			result += ((c - 'a') + 10);
		i++;
	}
	return (result);
}

void			ul64hex_to_stdout(unsigned long ul64)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (i < 16)
	{
		c = (ul64 >> (60 - (i * 4))) & 0xf;
		if (c < 10)
			c += '0';
		else
			c += ('a' - 10);
		write(1, &c, 1);
		i++;
	}
}
