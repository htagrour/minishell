#include "minishell.h"


int main (void)
{
    char *line;
    t_command *commands;
    int exe_return;
    int comm_number;

    // int i = 1;
    // while (i > 0)
    // {
    //     printf("my_shell");
    //     i = get_next_line(1, &line);
    //     parse(line, &commands);
    //     exe_return = execute(commands, comm_number);
    //     free(line);
    //     free_command_struct(commands, comm_number);
    // }

    char **str;
    
    str = ft_split("hello\";\"hi;cmd1;cmd2", ';');
    return 0;
}
