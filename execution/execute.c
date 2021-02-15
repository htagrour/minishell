#include "../minishell.h"



// i need to learn about muliple processing
int is_built_in(char *str)
{
    return (!strcmp(str,"cd") ||
            !strcmp(str,"echo")||
            !strcmp(str,"export") ||
            !strcmp(str,"cd")||
            !strcmp(str,"env")||
            !strcmp(str,"unset")||
            !strcmp(str,"pwd") ||
            !strcmp(str, "exit")
            );
}
int get_full_path(t_command *command, t_hash_map *hm)
{
    char *path;
    char **temp;
    char *cmd;
    char *temp1;
    void *temp2;
    struct stat st;
    int flag = -1;
    int i = -1;

    cmd = (char*)command->args->content;
    if (is_built_in(cmd) || (!stat(cmd, &st) && (st.st_mode & S_IXUSR)))
        return (0);
    path = get_value("PATH", hm);
    if (path[0])
    {
        temp = ft_split(path, ':');
        while (temp[++i])
        {
            temp1 = temp[i];
            temp[i] = ft_add_char(temp[i],'/');
            free(temp1);
            temp1 = ft_strjoin(temp[i], cmd);
            if (!stat(temp1, &st) && (st.st_mode & S_IXUSR))
            {
                flag = 0;
                break;
            }
            free(temp1);
        }
        free_array((void**)temp);
    }
    if (!flag)
    {
        temp2 = command->args->content;
        command->args->content = (void*)ft_strdup(temp1);
        free(temp2);
        free(temp1);
    }
    free(path);
    return (flag);
}

int get_in_fd(t_command command, int *last_fd)
{
    t_list *temp;
    struct stat st;
    t_redx *red;

    int fd;

    fd = *last_fd;
    temp = command.in_redx;
    while (temp)
    {   
        red = (t_redx*)temp->content;
        if ((fd = open(red->file,O_RDONLY)) < 0)
            return (-1);
        temp = temp->next;
    }
    *last_fd = fd;
    return (fd);
}

int get_out_fd(t_command command, int *out_fd)
{
    t_list *temp;
    struct stat st;
    int fd;
    t_redx *red;

    fd = *out_fd;
    temp = command.out_redx;
    while(temp)
    {   
        red = (t_redx*)temp->content;
        if (red->type)
            fd = open(red->file, O_RDWR | O_CREAT| O_APPEND, 0644);
        else
            fd = open(red->file, O_RDWR| O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            return (-1);
        temp = temp->next;
    }
    *out_fd = fd; 
    return (fd);
}

int execute_cmd(t_command *command, int *last_fd, int next_cmd, t_hash_map *env)
{
    int fd[2];
    pid_t pid;
    int ret;
    char **args;
    char **envs;

    pipe(fd);
    
    if (get_full_path(command, env) < 0)
        return (print_error("command not found", NULL));
    if (get_in_fd(*command,last_fd) < 0 ||  get_out_fd(*command ,&fd[1]) < 0)
    {
        *last_fd = fd[0];
        return (1);
    }
    if (!next_cmd && !built_in1(*command, env))
        return (0);
    envs = hash_to_arr(env);
    args = list_to_array(command->args);
    if((pid = fork()) == -1)
        exit(1);
    if (!pid)
    {
        dup2(*last_fd, 0);
        if (next_cmd || command->out_redx)
            dup2(fd[1], 1);
        close(fd[0]);
        if (built_in1(*command, env) &&  built_in2(args, envs))
                execve(*args, args, envs);
            exit(0);
    }
    wait(&ret);
    close(fd[1]);
    free_array((void**)args);
    free_array((void**)envs);
    *last_fd = fd[0];
 
    return ret;
}