#include "../minishell.h"


void free_array(void **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}

// void free_command_struct(t_command *commands, int struct_num)
// {
//     int i;

//     i = -1;
//     while (++i < struct_num)
//     {
//         free(commands[i].command);
//         free(commands[i].args);
//     }
// }