#include "../minishell.h"



// i need to learn about muliple processing
// void get_path();
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
        if (!lstat(red->file, &st) && (st.st_mode & S_IRUSR))
            fd = open(red->file, O_RDONLY);
        else
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
        // if (!lstat(red->file, &st) && (st.st_mode & S_IWUSR))
        if (!(fd = open(red->file, O_WRONLY| O_CREAT | O_APPEND)) < 0);
            return (-1);
        temp = temp->next;
    }
    *out_fd = fd; 
    return (fd);
}
int execute_cmd(t_command command, int *last_fd, int next_cmd, t_hash_map *env)
{
    int fd[2];
    pid_t pid;
    char **args;
    char **envs;
    struct dirent *de;
    //DIR *dr = opendir(get_value("PATH", env)); 

    args = list_to_array(command.args);
    pipe(fd);
    envs = hash_to_arr(env);
    if (get_in_fd(command,last_fd) < 0 ||  get_out_fd(command ,&fd[1]) < 0)
    {
        free_array((void**)args);
        free_array((void**)envs);
        *last_fd = fd[0];
        return (1);
    }
    //builtin_func(args, env, fd);
    //adjust_cmd(&command, env);
    if((pid = fork()) == -1)
        exit(1);
    if (!pid)
    {
        dup2(*last_fd, 0);
        if (next_cmd || command.out_redx)
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
    free_array((void**)envs);
    return 1;
}