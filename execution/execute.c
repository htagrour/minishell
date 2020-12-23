#include "../minishell.h"



// i need to learn about muliple processing 
int execute(t_command *commands, int comm_number)
{
    int value;
    int i;

    i = 0;
    while (i < comm_number)
    {
        if (ft_strncmp("echo", commands[i].command, 4))
            printf("%s\n", commands[i].args);
    }
    
    value = 0;
    return value;
}