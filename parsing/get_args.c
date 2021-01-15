#include "../minishell.h"
int ft_get_args(t_command *command, char *str)
{
    int value = 1;
    int i = 0;
    int flag = 0;
    char **temp;

    temp =  updated_split(str, ' ', &value);
    while(temp[i])
        printf("%s\n", temp[i++]);
    free_array((void**)temp);
    return value;
}