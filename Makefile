# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2020/12/14 05:50:41 by htagrour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell.a

SRC = get_next_line/get_next_line.c\
	  get_next_line/get_next_line_utils.c\
	  utils/utils.c\
	  libft/ft_split.c\
	  parsing/parse.c\
	  main.c

OBJECT = *.o

all: $(NAME)

$(NAME):

	gcc -Wall -Wextra -Werror -c $(SRC)  -D BUFFER_SIZE=10
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)
	gcc -Wall -Wextra -Werror $(NAME) -o minishell

clean:
	rm -f $(OBJECT) 
fclean: clean
	rm -f $(NAME)
	rm -f minishell
re: fclean all