/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 18:58:40 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 00:38:28 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*b64_insert_newlines(unsigned char *input, size_t *size)
{
	size_t			i;
	size_t			j;
	unsigned char	*output;

	if ((BASE64_LINE_LENGTH == 0) || (*size == 0))
		return (NULL);
	*size = *size + (*size / BASE64_LINE_LENGTH);
	if ((output = ft_memalloc(*size + 3)) == NULL)
		quit(errno, (input));
	i = 0;
	j = 0;
	while (i < *size)
	{
		output[i++] = (input)[j++];
		if (j % BASE64_LINE_LENGTH == 0)
			output[i++] = '\n';
	}
	if (output[(*size) - 1] != '\n')
		output[(*size)++] = '\n';
	return (output);
}

unsigned char	*b64_remove_newlines(unsigned char *input, size_t *size)
{
	size_t			i;
	size_t			j;
	unsigned char	*output;

	if (*size == 0)
		return (NULL);
	if ((output = ft_memalloc(*size + 3)) == NULL)
		quit(errno, input);
	i = 0;
	j = 0;
	while (j < *size)
	{
		if (input[j] == '\n')
			j++;
		else
			output[i++] = input[j++];
	}
	(*size) = i;
	return (output);
}
