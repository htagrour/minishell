/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 22:24:08 by htagrour          #+#    #+#             */
/*   Updated: 2021/04/05 16:00:27 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <termcap.h>
# include "../../../minishell.h"
# include "../libft/libft.h"
# define BUFFER_SIZE 1
# define CTR_D 4
# define DELETE 127
# define ARROW_UP 183
# define ARROW_DOWN 184
# define TAB 9

void	refresh(t_list *current);
int		put_char(int i);
int		get_next_line(int fd, char **line);
int		get_line(char **line, int fd, t_list **hist);
int		str_to_int(char *str);
int		clear_and_exit(void);

#endif
