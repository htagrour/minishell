#include "minishell.h"
#include <time.h>
void prints(void *str)
{
    printf("%s ", ((t_redirection*)str)->file);
}

void print_commands(t_command **commands)
{
    int i;
    int j;

    i = 0;
    while (commands[i])
    {
        printf("%d command\n", i);
        j = 0;
        while (commands[i][j].in_redx)
        {
           // printf("cmd:%s\n", commands[i][j].command);
           printf("in files: ");
           ft_lstiter(commands[i][j].in_redx, &prints);
           printf("\n");
           printf("out files: ");
           ft_lstiter(commands[i][j].out_redx, &prints);
           printf("\n");
        }
        
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
        //printf("\033[1;31m");
        ft_putstr_fd(BGRN, STDOUT_FILENO);
        ft_putstr_fd("my_shell> ", STDOUT_FILENO);
        ft_putstr_fd(RESET, STDOUT_FILENO);
        i = get_next_line(fd, &line);
        if (line)
            parse(line, &commands);
        print_commands(commands);
        //free commands array
        free(line);
        end = clock();
        timespend += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%fs\n", timespend);
    }
    return 0;
}
