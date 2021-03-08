#include "../minishell.h"

// int process_cmd(char *temp, int *last_fd,int next,t_hash_map *env)
// {
//     t_command *command;
//     int ret;
//     command = malloc(sizeof(t_command));
//     ft_bzero(command, sizeof(t_command));
//     if (get_cmd(command, temp, env))
//         return (-1);
//     ret = execute_cmd(command, last_fd, next, env);
//     free_command(command);
//     return (ret);
// }

// int run_pipe()
int process_line(char *line, t_hash_map *env)
{
    int i;
    char **temp1;
    char **temp2;
    int j;
    int last_fd;
    int ret;
    t_command *commands;
    
    i = 0;
    temp1 = updated_split(line, ';', &g_big_comm);
    if (!temp1)
        return (print_error("syntax error", 258, env));
    while (temp1[i])
    {
        j = -1;
        temp2 = updated_split(temp1[i], '|', &g_small_comm);
        if (!temp2)
            return (print_error("syntax error", 258, env));
        commands = (t_command*)malloc(sizeof(t_command) * g_small_comm);
        while (temp2[++j])
            if (get_cmd(&commands[j],temp2[j],env))
                break;
         execute_cmd(commands, 0, 0, j, env);
        free_array((void**)temp2);
        free_command_array(commands);
        i++;
    }
    free_array((void**)temp1);
    return 0;
}
