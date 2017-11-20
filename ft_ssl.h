/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:23 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/19 17:37:53 by asarandi         ###   ########.fr       */
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

# define BUF_SIZE 1024
# define DES_ENCRYPT 0
# define DES_DECRYPT 1

typedef unsigned long	t_ul;
typedef unsigned char	t_uc;

typedef struct			s_cmd
{
	int			enc;
	int			dec;
	int			b64;
	int			print;
	t_ul		master_key;
	t_ul		master_iv;
	char		*key;
	char		*iv;
	char		*input;
	char		*output;
}						t_cmd;

extern unsigned char	g_pc1_table[];
extern unsigned char	g_pc2_table[];
extern unsigned char	g_ip1_table[];
extern unsigned char	g_ip2_table[];
extern unsigned char	g_ebit_table[];
extern unsigned char	g_pperm_table[];
extern unsigned char	g_left_shifts[];
extern unsigned char	g_s1_box[];
extern unsigned char	g_s2_box[];
extern unsigned char	g_s3_box[];
extern unsigned char	g_s4_box[];
extern unsigned char	g_s5_box[];
extern unsigned char	g_s6_box[];
extern unsigned char	g_s7_box[];
extern unsigned char	g_s8_box[];
extern unsigned char	*g_s_boxes[];

int						ft_strequ(char const *s1, char const *s2);
int						is_valid_hex_key(unsigned char *s);
int						main(int ac, char **av);
size_t					ft_strlen(char const *s);
ssize_t					getfilesize(char *filename);
t_ul					cbc_get_iv(t_cmd *opt);
t_ul					ecb_get_key(t_cmd *opt);
t_uc					*base64decode(unsigned char *input, size_t *size);
t_uc					*base64encode(unsigned char *input, size_t *size);
t_uc					*ft_strtolower(unsigned char *s);
t_uc					*stdin_read_eof(size_t *count);
t_uc					*stdin_read_line(size_t *count);
t_uc					b64index(unsigned char c, t_uc *input, t_uc *output);
t_ul					circular_shift_left(unsigned long key, int bits);
t_ul					ecb_get_eight_bytes(unsigned char *data);
t_ul					ecb_process_block(t_ul input, t_ul keys[16]);
t_ul					get_s_boxes_value(unsigned long xor0);
t_ul					hex_to_ul64(unsigned char *s);
t_ul					hex_to_ul64_openssl(unsigned char *s);
t_ul					make_ebit(unsigned long r0);
t_ul					make_ip1(unsigned long m);
t_ul					make_ip2(unsigned long rxlx);
t_ul					make_pc1(unsigned long k);
t_ul					make_pc2(unsigned long c_half, unsigned long d_half);
t_ul					make_pperm(unsigned long sb0);
t_ul					text_to_ul64(unsigned char *s);
void					ecb_crypto(t_uc **input, size_t size, t_ul mk, int enc);
void					ecb_put_eight_bytes(unsigned char *data, t_ul ul64);
void					ft_putstr(char const *s);
void					b64enc_algo(t_uc *input, t_uc *output, size_t size);
void					*ft_memalloc(size_t size);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*getfilecontents(char *filename, size_t *size);
void					cbc_hex_iv_invalid_format(void *memory);
void					cbc_print_key(t_cmd opt);
void					cmd_base64(int ac, char **av);
void					cmd_cbc(int ac, char **av);
void					cmd_ecb(int ac, char **av);
void					ecb_hex_key_invalid_format(void *memory);
void					ecb_print_key(unsigned long master_key);
void					get_options(int i, int ac, char **av, t_cmd *opt);
void					init_options(t_cmd *opt);
void					list_commands(char **av);
void					parse_commands(int ac, char **av);
void					quit(int errnum, void *memory);
void					show_options(char *s);
void					ul64hex_to_stdout(unsigned long ul64);
void					cbc_decrypt(t_uc **in, size_t sz, t_cmd *opt, int enc);
void					cbc_encrypt(t_uc **in, size_t sz, t_cmd *opt, int enc);
void					make_half_keys	(t_ul half_keys[16], t_ul starter);
void					make_keys(t_ul keys[16], t_ul master_key, int rev);
void					cbc_decrypt_input
								(t_cmd *opt, t_uc **i, t_uc **o, size_t *sz);
void					cbc_encrypt_input
								(t_cmd *opt, t_uc **i, t_uc **o, size_t *sz);
void					ecb_decrypt_input
								(t_cmd *opt, t_uc **i, t_uc **o, size_t *sz);
void					ecb_encrypt_input
								(t_cmd *opt, t_uc **i, t_uc **o, size_t *sz);
void					get_input(t_cmd *opt, t_uc **i, size_t *size);
void					putfilecontents(char *fn, t_uc *data, size_t size);
#endif
