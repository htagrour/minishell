#ifndef MINISHELL_H
#define MINISHELL_H
#include "get_line/get_next_line.h"
#include "library/libft.h"
#include "hash_table/hash_table.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
// #include <wait.h>
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
} t_redx;

typedef struct s_command
{
    t_list *args;
    int next;
    t_list *in_redx; //type = 0;
    t_list *out_redx; // type = 1;
} t_command;
t_list *error;

int     g_big_comm;
int     g_small_comm;
char	**updated_split(char const *str, char del, int *ele_number);
int     process_line(char *line, t_hash_map *hm);
int	free_array(void **array);
int free_command_array(t_command *commands,int total);
int     execute(t_command *commande, int comm_number);
int     get_cmd(t_command *command, char *str, t_hash_map *hm);
void    adjust_var_bag(t_var_bag *bag, char c);
char    **list_to_array(t_list *list);
int     belong(char *str, char c);
int     is_red(char c);
int     conditions(char c, t_var_bag bag, char n);
char	*get_env(char *str, char **ptr, int len, t_hash_map *hm);
int     execute_commands(t_command *command, int last_fd,int total, t_hash_map *env);
void   free_command(t_command *command);
void    print_command(t_command commands ,t_hash_map *env);
int built_in1(t_command command, t_hash_map *hm);
int built_in2(char **args, t_hash_map *env);
int    print_error(char *str, int error, t_hash_map *env);
void sighandler(int signum);
#endif
