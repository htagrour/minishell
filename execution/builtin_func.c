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
    char *path;

    if (command.args->next->next)
        //too many args
        return (1);
    path =(char*) command.args->next->content;
    if (chdir(path) != 0)
    //error there no such path
        return (-1);
    // set_value("PWD", getcwd(), hm);
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
        temp = temp->next;
    }
    
    return 1;
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
        // else
            //error
            // ft_lst_add_front(error, )
        temp = temp->next;
    }
    return (1);
}
int built_in1(t_command command, t_hash_map *hm)
{
    char *cmd;
    int res;

    res = 1;
    cmd = (char*)command.args->content;
    if(!strcmp("cd", cmd))
        res = cd(command, hm);
    // if (!strcmp())
    return (res);    
}