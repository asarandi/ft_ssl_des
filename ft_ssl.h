/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:23 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/15 21:16:45 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <pwd.h>

#define BUF_SIZE 1024

typedef struct  s_cmd
{
        int             enc;
        int             dec;
        int             b64;
        char    *key;
        char    *iv;
        char    *input;
        char    *output;

}       t_cmd;

typedef	unsigned char	t_uc;

int		ft_strequ(char const *s1, char const *s2);
int	cmd_cbc(int ac, char **av);
int	cmd_ecb(int ac, char **av);
int	list_commands(int ac, char **av);
int	main(int ac, char **av);
int	parse_command(int ac, char **av);
size_t	ft_strlen(char const *s);
ssize_t	getfilesize(char *filename);
unsigned char	*base64decode(unsigned char *input, size_t *size);
unsigned char	*base64encode(unsigned char *input, size_t *size);
unsigned char	*read_stdin(size_t *count);
unsigned char	b64index(unsigned char c, t_uc *input, t_uc *output);
void	*ft_memalloc(size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*getfilecontents(char *filename, size_t *size);
void	b64enc_algo(t_uc *input, t_uc *output, size_t size);
void	cmd_base64(int ac, char **av);
void	ft_putstr(char const *s);
void	get_options(int ac, char **av, t_cmd *opt);
void	init_options(t_cmd *opt);
void	putfilecontents(char *filename, t_uc *data, size_t size, int line);
void	quit(int errnum, void *memory);
void	show_options(char *s);

#endif
