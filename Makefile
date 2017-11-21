# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/14 21:58:12 by asarandi          #+#    #+#              #
#    Updated: 2017/11/20 17:10:46 by asarandi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl
CC		= gcc
CFLAGS	= -O3 -Wall -Werror -Wextra
SRC		=	b64_utils.c \
			base64.c \
			cbc.c \
			cbc_utils.c \
			commands.c \
			des.c \
			des3.c \
			des3cbc.c \
			des3ecb.c \
			des_keys.c \
			des_tables.c \
			ecb.c \
			ecb_utils.c \
			file_op.c \
			main.c \
			memory_op.c \
			options.c \
			stdin_read.c \
			string_op.c \
			text_op.c
OBJ		= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

debug: fclean
	$(CC) -g -c $(SRC)
	$(CC) -g $(OBJ) -o debug

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) debug

re: fclean all
