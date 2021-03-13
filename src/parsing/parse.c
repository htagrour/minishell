#include "../minishell.h"

t_command *get_commands(char **temp, int total, t_hash_map *env)
{
    t_command *commands;
    int         i;

    commands = (t_command*) malloc(sizeof(t_command) * (total));
    if (!commands)
        return (NULL);
    i = -1;
    while (temp[++i])
    {
        if (get_cmd(&commands[i], temp[i], env))
        {
            free_array((void**)temp);
            free_command_array(commands, total);
            return (NULL);
        }
        commands[i].next = (temp[i+1] != NULL);
        free(temp[i]);
    }
    free(temp);
    return (commands);
}
