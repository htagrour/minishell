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

#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))


typedef struct s_var_bag
{
    int		brack_flag;
	char 	prev_char;
	char	spec_char;
    int     slash_flag;
} t_var_bag;

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

int     g_big_comm;
int     g_small_comm;
char	**updated_split(char const *str, char del, int *ele_number);
t_command		**parse(char *line);
void	free_array(void **array);
void    free_command_array(t_command **commands);
int     execute(t_command *commande, int comm_number);
int     ft_get_args(t_command *t_command, char *str);
void    adjust_var_bag(t_var_bag *bag, char c ,int i);
char    **list_to_array(t_list *list);
char    **get_final_args(t_list *list);
#endif
