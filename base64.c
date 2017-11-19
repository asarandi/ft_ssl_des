/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 20:14:04 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 01:38:50 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	b64index(unsigned char c, t_uc *input, t_uc *output)
{
	if ((c >= 'A') && (c <= 'Z'))
		return (c - 'A');
	else if ((c >= 'a') && (c <= 'z'))
		return (c - 'a' + 26);
	else if ((c >= '0') && (c <= '9'))
		return (c - '0' + 52);
	else if (c == '+')
		return (62);
	else if (c == '/')
		return (63);
	else if (c == '=')
		return (0);
	free(input);
	free(output);
	ft_putstr("Invalid character in input stream.\n");
	exit(-1);
}

size_t			b64dec_algo(t_uc *input, t_uc *output, size_t size)
{
	unsigned char	c;
	size_t			i;
	size_t			k;

	i = 0;
	k = 0;
	while (i < size)
	{
		output[k] = b64index(input[i++], input, output) << 2;
		c = b64index(input[i++], input, output);
		output[k++] += (c >> 4) & 0x3;
		output[k] = (c & 0xf) << 4;
		c = b64index(input[i++], input, output);
		output[k++] += (c >> 2) & 0xf;
		output[k] = (c & 0x3) << 6;
		output[k++] += b64index(input[i++], input, output) & 0x3f;
	}
	if ((input[i - 1] == '=') && (input[i - 2] == '='))
		output[--k] = 0;
	if (input[i - 1] == '=')
		output[--k] = 0;
	return (k);
}

unsigned char	*base64decode(unsigned char *input, size_t *size)
{
	unsigned char	*output;
	size_t			i;

	if (input[*size - 1] == '\n')
		input[--(*size)] = 0;
	i = (*size / 4) * 3;
	if ((output = ft_memalloc(i + 6)) == NULL)
		quit(errno, input);
	*size = b64dec_algo(input, output, *size);
	return (output);
}

void			b64enc_algo(t_uc *input, t_uc *output, size_t size)
{
	unsigned char	c;
	static char		*tab;
	size_t			i;
	size_t			k;

	tab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	i = 0;
	k = 0;
	while (i < size)
	{
		output[k++] = tab[input[i] >> 2];
		c = input[i++] << 6;
		output[k++] = tab[(c >> 2) + (input[i] >> 4)];
		c = input[i++] << 4;
		output[k++] = tab[(c >> 2) + (input[i] >> 6)];
		c = ((input[i++]) << 2);
		output[k++] = tab[c >> 2];
	}
	if (i - 2 == size)
		output[k - 2] = '=';
	if (i - 1 >= size)
		output[k - 1] = '=';
}

unsigned char	*base64encode(unsigned char *input, size_t *size)
{
	unsigned char	*output;
	unsigned char	*padded;
	size_t			i;

	if ((padded = ft_memalloc(*size + 6)) == NULL)
		quit(errno, input);
	ft_memcpy(padded, input, *size);
	i = *size;
	while (i % 3)
		i++;
	i /= 3;
	i *= 4;
	if ((output = ft_memalloc(i + 1)) == NULL)
	{
		free(padded);
		quit(errno, input);
	}
	b64enc_algo(padded, output, *size);
	*size = ft_strlen((char *)output);
	output[(*size)++] = '\n';
	free(padded);
	return (output);
}
