# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/14 21:58:12 by asarandi          #+#    #+#              #
#    Updated: 2017/11/15 15:53:51 by asarandi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
SRC		= $(wildcard *.c)
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
