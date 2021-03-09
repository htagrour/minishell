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

int process_line(char *line, t_hash_map *env)
{
    t_command *commands;
    char **temp1;
    char **temp2;
    int i;
    int total;
    
    temp1 = updated_split(line, ';', &i);
    if (!temp1)
        return (print_error("syntax error", 258, env));
    i = -1;
    while (temp1[++i])
    {
        temp2 = updated_split(temp1[i], '|', &total);
        if (!temp2)
            return (print_error("syntax error", 258, env));
        if (!(commands = get_commands(temp2, total, env)))
            return (free_array((void**)temp1));
        execute_commands(commands, 0, total, env);
        free_command_array(commands, total);
    }
    free_array((void**)temp1);
    return 0;
}