#ifndef MINISHELL_H
#define MINISHELL_H
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define RED "\e[0;31m"
#define RESET "\e[0m"
#define BLKHB "\e[0;100m"
#define BGRN "\e[1;32m"


typedef struct s_command
{
    char *command;
    char **args;
    int input;
    int output;
} t_command;

// typedef struct s_list
// {
//     char *part;
//     struct  s_list *next;
    
// } t_list;
//utils
char	**updated_split(char const *str, char del, int *ele_number);
int		parse(char *line, t_command ***commands);
void	free_array(void **array);
void    free_command_struct(t_command *commands, int struct_num);
int     execute(t_command *commande, int comm_number);
// void	ft_lstadd_front(t_list **alst, t_list *new);
// t_list			*ft_lstnew(char *part);
#endif
