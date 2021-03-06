#include "../minishell.h"

int process_cmd(t_command *command, char *temp,t_hash_map *env)
{
    ft_bzero(command, sizeof(t_command));
    if (get_cmd(command, temp, env))
        return (-1);
    return (0);
}

int process_line(char *line, t_hash_map *env)
{
    int i;
    char **temp1;
    char **temp2;
    int j;
    int last_fd;
    int ret;
    t_command *command;

    i = 0;
    last_fd = 0;
    temp1 = updated_split(line, ';', &g_big_comm);
    if (!temp1)
        return (print_error("syntax error", 258, env));
    while (temp1[i])
    {
        j = -1;
        temp2 = updated_split(temp1[i], '|', &g_small_comm);
        if (!temp2)
            return (print_error("syntax error", 258, env));
        command = malloc(sizeof(t_command)* g_small_comm);
        while (temp2[++j])
        {
            if (process_cmd(&command[j],temp2[j], env) < 0)
                break;
        }
        free_array((void**)temp2);
        execute(command, env, g_small_comm);
        i++;
    }
    free_array((void**)temp1);
    return 0;
}
