#include "../minishell.h"

// simple splite using ; as delimetor
int parse(char *line, t_command **commands)
{
    int value;
    char **str;
    char **temp;
    int i;

    str = ft_split(line, ';');
    value = ft_array_len((void **)str);
    *commands = malloc(sizeof(t_command) * i);
    i = 0;
    while (str[i])
    {
        temp = ft_split(str[i], ' ');
        commands[i]->command = ft_strdup(temp[0]);
        commands[i]->args = ft_strdup(temp[1]);
        i++;
    }
    free_array((void**)str);
    free_array((void**)temp);
    return value;
}