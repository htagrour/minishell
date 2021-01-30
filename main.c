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
    while (i < 1)
    {
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
        i++;
        
    }
}
int main (void)
{
    char *line;
    double timespend;
    t_command **commands;
    clock_t begin;
    clock_t end;
    int i = 1;
    int j;
    int fd = open("test.txt", O_RDONLY);
    while (i > 0)
    {
        timespend = 0.0;
        begin = clock();
        ft_putstr_fd(BGRN, STDOUT_FILENO);
        ft_putstr_fd("my_shell> ", STDOUT_FILENO);
        ft_putstr_fd(RESET, STDOUT_FILENO);
        i = get_next_line(fd, &line);
        if (line[0])
        {
            parse(line, &commands);
            print_commands(commands);
        }
        free_command_array(&commands);
        free(line);
        end = clock();
        timespend += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%fs\n", timespend);
    }
    return 0;
}
