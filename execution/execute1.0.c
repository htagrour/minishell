#include "minishell.h"

int        execute_cmds(t_command *command, t_hash_map *env, int total)
{
    int *fds;
    int i;
    int pid;

    i = -1;
    fds = malloc(sizeof(int) * total * 2);
    if (!fds)
        return (-1);
    while(++i < total)
        pipe(fds + (i * 2));
    i = -1;
    while (++i < total)
    {
        if (!(pid = fork()))
        {
            if (get_in_fd(&command,&fds[(i - 1) * 2]) < 0 ||  get_out_fd(&command ,&fds[i * 2 + 1]) < 0)
                return (print_error("file error", 1, env));
            execute_cmd(command[i], )
        }
    }
    i = -1;
    while (++i < total * 2)
        close(fds[i]);
    while (++i < total)
        wait(NULL);
    return (0);
}