#include "../minishell.h"

int process_cmd(char *temp, int *last_fd,int next,t_hash_map *env)
{
    t_command *command;
    
    command = malloc(sizeof(t_command));
    ft_bzero(command, sizeof(t_command));
    if (get_cmd(command, temp, env) < 0)
        return (print_error("PARSE ERROR", NULL));
   // print_command(*command, env);
    execute_cmd(command, last_fd, next, env);
    free_command(command);
    return (1);
}

int process_line(char *line, t_hash_map *env, t_list **errors)
{
    int i;
    char **temp1;
    char **temp2;
    int j;
    int last_fd;

    i = 0;
    last_fd = 0;
    temp1 = updated_split(line, ';', &g_big_comm);
    if (!temp1)
        return (print_error("PARSE ERROR", errors));
    while (temp1[i])
    {
        j = -1;
        temp2 = updated_split(temp1[i], '|', &g_small_comm);
        if (!temp2)
            return (print_error("PARSE ERROR", errors));
        while (temp2[++j])
            process_cmd(temp2[j], &last_fd,temp2[j + 1] != 0,env);
        free_array((void**)temp2);
        i++;
    }
    free_array((void**)temp1);
    return 0;
}
