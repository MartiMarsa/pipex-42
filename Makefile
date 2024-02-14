# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 12:51:18 by mmarsa-s          #+#    #+#              #
#    Updated: 2024/02/13 12:51:20 by mmarsa-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC = main.c childs.c aux.c
OBJ = $(SRC:.c=.o)

SRC_LIBFT = ./libft/libft.a
MAKE_LIBFT = make -C libft --no-print-directory

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: make_libft $(NAME)

make_libft:
	$(MAKE_LIBFT)

$(NAME): $(OBJ) $(SRC_LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
