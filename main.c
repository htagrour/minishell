#include "minishell.h"


int main (void)
{
    char *line;
    t_command **commands;

    int i = 1;
    int j;
    int fd = open("test.txt", O_RDONLY);
    while (i > 0)
    {
        //printf("\033[1;31m");
        ft_putstr_fd(BGRN, STDOUT_FILENO);
        ft_putstr_fd("my_shell> ", STDOUT_FILENO);
        ft_putstr_fd(RESET, STDOUT_FILENO);
        i = get_next_line(STDIN_FILENO, &line);
        parse(line, &commands);
        //free commands array
        free(line);
    }
    return 0;
}
