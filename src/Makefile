# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2021/03/08 18:05:00 by htagrour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell.a

SRC = 	get_line/*.c\
		library/*.c\
		parsing/*.c\
		utils/*.c\
		execution/*.c\
		hash_table/*.c\
		main.c

OBJECT = *.o

all: $(NAME)

$(NAME):

	gcc -c $(SRC)  -D BUFFER_SIZE=10 -g
	#-Wall -Wextra -Werror
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)
	gcc  $(NAME) -fsanitize=address -o minishell -g
	rm -f $(OBJECT) 

clean:
	rm -f $(OBJECT) 
fclean: clean
	rm -f $(NAME)
	rm -f minishell
re: fclean all
