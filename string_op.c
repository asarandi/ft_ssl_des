/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 23:47:10 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 01:57:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*ft_strtolower(unsigned char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 'A') && (s[i] <= 'Z'))
			s[i] += 32;
		i++;
	}
	return (s);
}

size_t			ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void			ft_putstr(char const *s)
{
	size_t	size;

	size = ft_strlen(s);
	write(1, s, size);
	return ;
}

int				ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}
