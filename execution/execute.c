#include "../minishell.h"



// i need to learn about muliple processing
// void get_path();
int execute_cmd(t_command command, int *last_fd, int next_cmd, t_hash_map *env)
{
    int fd[2];
    pid_t pid;
    char **args;
    char **envs;
    struct dirent *de;
    DIR *dr = opendir(get_value("PATH", env)); 

    args = list_to_array(command.args);
    pipe(fd);
    //fd[0] = get_in_file(command.in_redx);
    //fd[1] = get_out_file(command.out_redx); 
    //builtin_func(args, env, fd);
    //adjust_cmd(&command, env);
    if((pid = fork()) == -1)
        exit(1);
    if (!pid)
    {
        dup2(*last_fd, 0);
        if (next_cmd)
            dup2(fd[1], 1);
        close(fd[0]);
        //is built in function
        execve(*args, args, envs);
        exit(0);
    }
    wait(NULL);
    close(fd[1]);
    *last_fd = fd[0];
    free_array((void**)args);
    free_array((void*)env);
    return 1;
}