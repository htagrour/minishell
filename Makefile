# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2021/04/05 16:14:41 by htagrour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g -ltermcap

CFLAGS = -Wall -Wextra -Werror 

SRC = srcs/execution/*.c\
	srcs/utils/*.c\
	srcs/utils/get_line/*.c\
	srcs/utils/hash_table/*.c\
	srcs/parsing/*.c\
	srcs/utils/libft/*.c\
	*.c
	
all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) 
re:	fclean all
	
