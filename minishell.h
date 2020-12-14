#ifndef MINISHELL_H
#define MINISHELL_H
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>


int		parse(char *line);
void	free_array(void **array);
#endif
