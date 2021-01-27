#ifndef MINISHELL_H
#define MINISHELL_H
#include "get_line/get_next_line.h"
#include "library/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define RED "\e[0;31m"
#define RESET "\e[0m"
#define BLKHB "\e[0;100m"
#define BGRN "\e[1;32m"

typedef struct  s_redirection
{
    int type;
    char *file;
} t_redirection;

typedef struct s_command
{
    char *command;
    t_list *args;
    int test;
    t_list *in_redx; //type = 0;
    t_list *out_redx; // type = 1;
} t_command;


char	**updated_split(char const *str, char del, int *ele_number);
int		parse(char *line, t_command ***commands);
void	free_array(void **array);
void    free_command_struct(t_command *commands, int struct_num);
int     execute(t_command *commande, int comm_number);
int     ft_get_args(t_command *t_command, char *str);
// void	ft_lstadd_front(t_list **alst, t_list *new);
// t_list			*ft_lstnew(char *part);
#endif
