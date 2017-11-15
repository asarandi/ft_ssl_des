/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:23 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/15 02:58:37 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

typedef	unsigned char t_uc;

char	*b64enc_algo(size_t k, size_t size, char *output, unsigned char *s);
char	*base64encode(unsigned char *input, size_t size);
int		ft_strequ(char const *s1, char const *s2);
int		getfilesize(char *filename);
int		cmd_base64(int ac, char **av);
int		cmd_cbc(int ac, char **av);
int		cmd_ecb(int ac, char **av);
int		list_commands(int ac, char **av);
int		main(int ac, char **av);
int		parse_command(int ac, char **av);
t_uc	*read_stdin(size_t *count);
void	*ft_memalloc(size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*getfilecontents(char *filename);
void	ft_putstr(char const *s);
void	quit(int errnum, void *memory);


#endif
