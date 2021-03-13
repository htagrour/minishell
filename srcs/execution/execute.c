/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:58 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/13 19:16:02 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void add_return(t_hash_map *env, int ret)
{
    char *temp;

    temp = ft_itoa(ret);
    set_value("?",temp, env);
    free(temp);
}

char *get_bin(char *cmd, struct stat st,t_hash_map *env)
{
    char *temp1;
    char **temp;
    char *path;
    int     i;

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
    struct stat st;
    char *bin;
    char *cmd;

    if (!command->args)
        return (1);
    cmd = (char*)command->args->content;

    if (is_built_in(cmd) || (!stat(cmd, &st) && (st.st_mode & S_IXUSR)))
        return (0);
    if (!(bin = get_bin(cmd, st,env)))
        return (127);
    free(command->args->content);
    command->args->content = (void*)ft_strdup(bin);
    free(bin);
    return (0);
}

int get_in_fd(t_command command, int *last_fd)
{
    t_list *temp;
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


void sig_default_mode()
{
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
}

void connect_pipes(t_command command, int last_fd, int fds[])
{
        dup2(last_fd, 0);
        if (last_fd != 0)
            close(last_fd);
        if (command.next || command.out_redx)
            dup2(fds[1], 1);
        close(fds[0]);
        close(fds[1]);

}
int start_process(t_command command, int last_fd, int fds[], t_hash_map *env)
{
    char **envs;
    char **args;
    pid_t pid;

    if((pid = fork()) == -1)
        exit(1);
    if (!pid)
    {   sig_default_mode();
        if (get_in_fd(command, &last_fd)|| get_out_fd(command, &fds[1]))
            exit(print_error("FIle ERROR", 1,env));
        if (get_full_path(&command, env))
            exit(print_error("command not found", 127,env));
        connect_pipes(command, last_fd, fds);
        envs = hash_to_arr(env);
        args = list_to_array(command.args);
        if (built_in1(command, env) &&  built_in2(args, env))
                execve(*args, args, envs);
        else
            exit(EXIT_SUCCESS);
        exit(EXIT_FAILURE);
    }
    close(fds[1]);
    return (pid);
}

int get_return_status(int ret, t_hash_map *env, t_command *command)
{
    if (!command->next)
    {
        if (WIFEXITED(ret))
            add_return(env,WEXITSTATUS(ret));
        if (WIFSIGNALED(ret))
            add_return(env, WTERMSIG(ret) + 128);

    }
    return (0);
}
int execute_commands(t_command *commands, int last_fd,int total, t_hash_map *env)
{
    int fds[2];
    int ret;

    if ((total == 1) && built_in1(*commands, env) != -1)
        return (0);
    pipe(fds);
    int pid = start_process(*commands, last_fd,fds, env);
    if (commands->next)
        ret = execute_commands(commands+1, fds[0],total,env);
    close(fds[0]);
    waitpid(pid,&ret, 0);
    return (get_return_status(ret, env, commands));
}
