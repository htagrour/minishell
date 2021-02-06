#include "minishell.h"
#include <time.h>

void prints(void *str)
{
    printf("%s\n", ((t_redirection*)str)->file);
}

void printss(void *str)
{
    printf("%s\n", (char*)str);
}
void print_array(char **tab)
{
    while (*tab)
    {
        printf("%s\n", *tab);
        tab++;
    }
    
}
void print_commands(t_command **commands)
{
    int i;
    int j;

    char **tab;
    i = 0;
    while (i < g_big_comm)
    {   
        g_small_comm = commands[i][0].test;
        j = 0;
        while (j < g_small_comm)
        {
          // printf("cmd:%s\n", commands[i][j].command);
          tab = get_final_args(commands[i][j].args);
          print_array(tab);
          free_array((void**)tab);
           j++;
        }
        printf("---------------------------------------\n");
        i++;
        
    }
}
int main (void)
{
    char *line;
    t_command **commands;
    t_hash_map *env;

    int i = 1;
    int fd = open("test.txt", O_RDONLY);
    env = init_hash_map(100);
    while (i > 0)
    {
        ft_putstr_fd(BGRN, STDOUT_FILENO);
        ft_putstr_fd("my_shell> ", STDOUT_FILENO);
        ft_putstr_fd(RESET, STDOUT_FILENO);
        i = get_next_line(fd, &line);
        if (line[0])
        {
            commands = parse(line);
            print_commands(commands);
            //execute(commands, env);
            free_command_array(commands);
        }
        printf("\n");
        free(line);
    }
    free_hash_map(env);
    return 0;
}
