/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 20:14:04 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/15 02:48:33 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*b64enc_algo(size_t k, size_t size, char *output, unsigned char *s)
{
	unsigned char	c;
	unsigned char	d;
	static char		*tab;
	size_t			i;

	tab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	i = 0;
	while (i < size)
	{
		c = s[i] >> 2;
		output[k++] = tab[c];
		c = s[i++] << 6;
		d = s[i] >> 4;
		output[k++] = tab[(c >> 2) + d];
		c = s[i++] << 4;
		d = s[i] >> 6;
		output[k++] = tab[(c >> 2) + d];
		c = ((s[i++]) << 2);
		output[k++] = tab[c >> 2];
	}
	if (i - 2 == size)
		output[k - 2] = '=';
	if (i - 1 >= size)
		output[k - 1] = '=';
	return (output);
}

char	*base64encode(unsigned char *input, size_t size)
{
	char			*output;
	unsigned char	*padded;
	size_t			i;

	if ((padded = ft_memalloc(size + 6)) == NULL)
		quit(errno, input);
	ft_memcpy(padded, input, size);
	i = size;
	while (i % 3)
		i++;
	i /= 3;
	i *= 4;
	if ((output = ft_memalloc(i + 1)) == NULL)
	{
		free(padded);
		quit(errno, input);
	}
	b64enc_algo(0, size, output, padded);
	free(padded);
	return (output);
}
