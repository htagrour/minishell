#include "minishell.h"
#include <time.h>

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
        i = get_next_line(STDIN_FILENO, &line);
        if (line)
            parse(line, &commands);
        //free commands array
        free(line);
        end = clock();
        timespend += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%fs\n", timespend);
    }
    return 0;
}
