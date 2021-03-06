/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:23 by asarandi          #+#    #+#             */
/*   Updated: 2017/11/20 17:06:01 by asarandi         ###   ########.fr       */
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
# define BASE64_LINE_LENGTH 64

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
	t_ul		des3_key1;
	t_ul		des3_key2;
	t_ul		des3_key3;
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
unsigned long			cbc_get_iv(t_cmd *opt);
unsigned long			ecb_get_key(t_cmd *opt);
unsigned char			*b64_insert_newlines(t_uc *input, size_t *size);
unsigned char			*b64_remove_newlines(t_uc *input, size_t *size);
unsigned char			*base64decode(unsigned char *input, size_t *size);
unsigned char			*base64encode(unsigned char *input, size_t *size);
unsigned char			*ft_strtolower(unsigned char *s);
unsigned char			*stdin_read_eof(size_t *count);
unsigned char			*stdin_read_line(size_t *count);
unsigned char			b64index(t_uc c, t_uc *input, t_uc *output);
unsigned long			circular_shift_left(unsigned long key, int bits);
unsigned long			ecb_get_eight_bytes(unsigned char *data);
unsigned long			ecb_process_block(t_ul input, t_ul keys[16]);
unsigned long			get_s_boxes_value(unsigned long xor0);
unsigned long			hex_to_ul64(unsigned char *s);
unsigned long			make_ebit(unsigned long r0);
unsigned long			make_ip1(unsigned long m);
unsigned long			make_ip2(unsigned long rxlx);
unsigned long			make_pc1(unsigned long k);
unsigned long			make_pc2(unsigned long c_half, unsigned long d_half);
unsigned long			make_pperm(unsigned long sb0);
unsigned long			text_to_ul64(unsigned char *s);
void					b64enc_algo(t_uc *input, t_uc *output, size_t size);
void					cbc_decrypt(t_uc **inp, size_t sz, t_cmd *opt, int enc);
void					cbc_encrypt(t_uc **inp, size_t sz, t_cmd *opt, int enc);
void					ecb_crypto(t_uc **input, size_t size, t_ul mk, int enc);
void					ecb_put_eight_bytes(unsigned char *data, t_ul ul64);
void					ft_putstr(char const *s);
void					make_half_keys(t_ul half_keys[16], t_ul starter);
void					make_keys(t_ul keys[16], t_ul master_key, int rev);
void					ul64hex_to_stdout(unsigned long ul64);
void					*ft_memalloc(size_t size);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*getfilecontents(char *filename, size_t *size);
void					cbc_hex_iv_invalid_format(void *memory);
void					cbc_print_key(t_cmd opt);
void					cmd_base64(int ac, char **av);
void					cmd_cbc(int ac, char **av);
void					cmd_des3cbc(int ac, char **av);
void					cmd_des3ecb(int ac, char **av);
void					cmd_ecb(int ac, char **av);
void					ecb_hex_key_invalid_format(void *memory);
void					ecb_print_key(unsigned long master_key);
void					get_input(t_cmd *opt, t_uc **input, size_t *size);
void					get_options(int i, int ac, char **av, t_cmd *opt);
void					get_triple_key(unsigned char *str_key, t_cmd *opt);
void					init_options(t_cmd *opt);
void					list_commands(char **av);
void					parse_commands(int ac, char **av);
void					putfilecontents(char *fname, t_uc *data, size_t size);
void					quit(int errnum, void *memory);
void					show_options(char *s);
void					des3_get_key(t_cmd *opt);
void					des3_print_key(t_cmd *opt, int print_iv);
void					des3ecb_decrypt(t_uc **input, size_t size, t_cmd *opt);
void					des3ecb_encrypt(t_uc **input, size_t size, t_cmd *opt);
void					des3cbc_encrypt(t_uc **input, size_t size, t_cmd *opt);
void					des3cbc_encrypt_input
						(t_cmd *opt, t_uc **in, t_uc **out, size_t *sz);
void					des3cbc_decrypt
						(t_uc **input, size_t size, t_cmd *opt, t_ul next_iv);
void					des3cbc_decrypt_input
						(t_cmd *opt, t_uc **in, t_uc **out, size_t *sz);
void					cbc_decrypt_input
						(t_cmd *opt, t_uc **input, t_uc **output, size_t *size);
void					cbc_encrypt_input
						(t_cmd *opt, t_uc **input, t_uc **output, size_t *size);
void					ecb_decrypt_input
						(t_cmd *opt, t_uc **input, t_uc **output, size_t *size);
void					ecb_encrypt_input
						(t_cmd *opt, t_uc **input, t_uc **output, size_t *size);
void					des3ecb_decrypt_input
						(t_cmd *opt, t_uc **in, t_uc **out, size_t *sz);
void					des3ecb_encrypt_input
						(t_cmd *opt, t_uc **in, t_uc **out, size_t *sz);

#endif
