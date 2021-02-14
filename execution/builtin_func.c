#include "../minishell.h"

int is_valide_var(char *str)
{   
    if (ft_isdigit(*str))
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

int cd(t_command command, t_hash_map *hm)
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
        return (print_error("PATH not exist or a file", NULL));
    set_value("PWD", path, hm);
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

    temp = command.args->next;
    while (temp)
    {
        str = ft_split((char *)temp->content, '=');
        if (is_valide_var(str[0]))
            set_value(str[0], str[1], env);
        else
            print_error("not valide identifier", NULL);
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
        temp = temp->next;
    }
    return (0);
}

int echo(t_command command)
{
    t_list *temp;
    int flag;

    flag = 0;
    temp = command.args->next;
    if (!strcmp((char*)temp->content, "-n"))
    {
        temp = temp->next;
        flag = 1;
    }
    while (temp)
    {
        ft_putstr_fd((char*)temp->content, STDOUT_FILENO);
        if ((temp = temp->next))
            ft_putstr_fd(" ", STDOUT_FILENO);
    }
    if (!flag)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}

int built_in1(t_command command, t_hash_map *env)
{
    char *cmd;
    int res;

    res = 1;
    cmd = (char*)command.args->content;
    if(!strcmp("cd", cmd))
        res = cd(command, env);
    if (!strcmp("unset", cmd))
        res = unset(command, env);
    if (!strcmp("export", cmd))
        res = export(command, env);
    if (!strcmp("exit", cmd))
        exit(0);
    return (res);    
}
int built_in2(t_command command)
{
    int res;
    char *cmd;
    res = 1;
    cmd = (char*) command.args->content;
    if (!strcmp(cmd,"echo"))
        res = echo(command);
    if (!strcmp(cmd, "pwd"))
        res = pwd();
    return (res);
}