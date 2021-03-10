#include "../minishell.h"

int is_valide_var(char *str)
{   
    if (!ft_isalpha(*str))
        return (0);
    str++;
    while (*str)
    {
        if (!(ft_isalnum(*str)))
            return 0;
        str++;
    }
    return 1;
}

int is_valide_exit(char *str)
{
    while (*str)
    {
        if (!(ft_isdigit(*str) || *str== '+' || *str == '-'))
            return (0);
        str++;
    }
    return (1);
}

int cd(t_command command, t_hash_map *env)
{
    char *temp;
    char *path;

    if (command.args->next)
    {
        temp =(char*) command.args->next->content;
        if (temp[0]== '~')
            path = ft_strjoin("/Users/htagrour", temp + 1);
        else
            path = ft_strdup(temp);
    }
    else
        path = ft_strdup("/Users/htagrour");
    if (chdir(path) != 0)
        return (print_error("PATH not exist or a file", 1, env));
    set_value("PWD", path, env);
    free(path);
    return (0);
}

int pwd()
{
    char *buff;

    buff = malloc(sizeof(char)*1024);
    ft_putendl_fd(getcwd(buff, 1024), STDOUT_FILENO);
    free(buff); 
    return (0);
}

int     export(t_command command, t_hash_map *env)
{
    char **str;
    t_list *temp;
    char **envs;

    temp = command.args->next;
    // if (!temp)
    // {
    //     envs = hash_to_arr(env);
    //     while (*envs)
    //     {
    //         /
    //     }
        
    // }
    while (temp)
    {
        str = ft_split((char *)temp->content, '=');
        if (is_valide_var(str[0]))
            set_value(str[0], str[1], env);
        else
            print_error("not valide identifier", 1, env);
        temp = temp->next;
    }
    return (0);
}

int unset(t_command command, t_hash_map *env)
{
    t_list *temp;
    char *str;

    temp = command.args->next;
    while (temp)
    {   str = (char*)temp->content;
        if (is_valide_var(str))
            delet_value(str, env);
        else
            print_error("not valide identifier", 1, env);
        temp = temp->next;
    }
    return (0);
}

int echo(char **args)
{
    int flag;

    flag = 0;
    args++;
    if (*args)
    {
        if (!strcmp(*args, "-n"))
        {
            args++;
            flag = 1;
        }
        while (*args)
        {
            ft_putstr_fd(*args, STDOUT_FILENO);
            if (*(args + 1))
                ft_putstr_fd(" ", STDOUT_FILENO);
            args++;
        }
    }
    if (!flag)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}

int env(char **args, t_hash_map *env)
{
    args++;
    char **envs;

    if (!*args)
    {
        envs = hash_to_arr(env);
        while(*envs)
        {
            ft_putendl_fd(*envs, STDOUT_FILENO);
            envs++;
        }
        free_array((void**)envs);
        return (0);
    }
    else
        return(print_error("env don't accept args", 1, env));
}
int exit_(t_command cmd, t_hash_map *env)
{
    t_list *temp;

    temp = cmd.args->next;
    if (!temp)
        exit(0);
    if (temp->next)
        return (print_error("exit: too many arguments", 1, env));
    if (!is_valide_exit((char*)temp->content))
        return (print_error("exit: numeric argument required", 255, env));
    exit(ft_atoi((char*)temp->content));
    return (0);
}

int built_in1(t_command command, t_hash_map *env)
{
    char *cmd;
    int res;

    res = -1;
    cmd = (char*)command.args->content;
    if(!strcmp("cd", cmd))
        res = cd(command, env);
    if (!strcmp("unset", cmd))
        res = unset(command, env);
    if (!strcmp("export", cmd))
        res = export(command, env);
    if (!strcmp("exit", cmd))
        res = exit_(command, env);
    return (res);    
}
int built_in2(char **args, t_hash_map *envs)
{
    int res;
    char *cmd;
    res = 1;
    if (!strcmp(*args,"echo"))
        res = echo(args);
    if (!strcmp(*args, "pwd"))
        res = pwd();
    if (!strcmp(*args, "env"))
        res = env(args, envs);
    return (res);
}