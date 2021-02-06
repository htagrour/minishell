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

void print_commands(t_command **commands)
{
    int i;
    int j;

    i = 0;
    while (i < g_big_comm)
    {   
        g_small_comm = commands[i][0].test;
        j = 0;
        while (j < 1)
        {
           printf("cmd:%s\n", commands[i][j].command);
           printf("args: ");
           ft_lstiter(commands[i][j].args, &printss);
           printf("\n");
           printf("in files: ");
           ft_lstiter(commands[i][j].in_redx, &prints);
           printf("\n");
           printf("out files: ");
           ft_lstiter(commands[i][j].out_redx, &prints);
           printf("\n");
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
    int i = 1;
    int j;
    int fd = open("test.txt", O_RDONLY);
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
            free_command_array(commands);
        }
        //free_command_array(commands);
        printf("\n");
        free(line);
    }
    return 0;
}