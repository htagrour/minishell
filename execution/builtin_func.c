#include "../minishell.h"

int all_char(char *str)
{
    while (*str)
    {
        if (!(ft_isalnum(*str)))
            return 0;
        str++;
    }
    return 1;
}

int cmd()
{
    return (1);
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
        if (all_char(str))
            delet_value(str, env);
        else
            //error
            // ft_lst_add_front(error, )
            return (0);
        temp = temp->next;
    }
    return (1);
}