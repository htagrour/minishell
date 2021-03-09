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

char *get_bin(t_command command, struct stat st,t_hash_map *env)
{
    char *cmd;
    char *temp1;
    char **temp;
    char *path;
    int     i;

    cmd = (char*)command.args->content;
    if (is_built_in(cmd) || (!stat(cmd, &st) && (st.st_mode & S_IXUSR)))
        return (0);
    path = get_value("PATH", env);
    if (path[0])
    {
        temp = ft_split(path, ':');
        free(path);
        i = -1;
        while (temp[++i])
        {
            temp1 = temp[i];
            temp[i] = ft_add_char(temp[i],'/');
            free(temp1);
            temp1 = ft_strjoin(temp[i], cmd);
            if (!stat(temp1, &st) && (st.st_mode & S_IXUSR))
                return (temp1);
            free(temp1);
        }
        free_array((void**)temp);
    }
    return (NULL);
}

int get_full_path(t_command *command, t_hash_map *env)
{
    char *temp1;
    struct stat st;
    char *bin;

    if (!command->args)
        return (1);
    if (!(bin = get_bin(*command, st,env)))
        return (127);
    free(command->args->content);
    command->args->content = (void*)ft_strdup(bin);
    free(bin);
    return (0);
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
    return (0);
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
    return (0);
}

int start_process(t_command command, int last_fd, int fds[], t_hash_map *env)
{
    char **envs;
    char **args;
    pid_t pid;

    if((pid = fork()) == -1)
        exit(1);
    if (!pid)
    {
        if (get_full_path(&command, env))
            exit(print_error("command not found", 127,env));
        dup2(last_fd, 0);
        if (last_fd != 0)
            close(last_fd);
        if (command.next || command.out_redx)
            dup2(fds[1], 1);
        close(fds[0]);
        close(fds[1]);
        envs = hash_to_arr(env);
        args = list_to_array(command.args);
        if (built_in1(command, env) &&  built_in2(args, env))
                execve(*args, args, envs);
        else
            exit(0);
        exit(1);
    }
    close(fds[1]);
}

int execute_commands(t_command *commands, int last_fd,int total, t_hash_map *env)
{
    int fds[2];
    char **args;
    char **envs;
    char *temp;
    int ret;

    pipe(fds);
    if (!get_in_fd(*commands,&last_fd) ||  !get_out_fd(*commands ,&fds[1]))
    {
        if ((total == 1) && built_in1(*commands, env) != -1)
            return (0);
        start_process(*commands, last_fd,fds, env);
        if (commands->next)
            ret = execute_commands(commands+1, fds[0],total,env);
        close(fds[0]);
        wait(NULL);
        return (ret);
    }
    else
        print_error("file error", 1, env);
}