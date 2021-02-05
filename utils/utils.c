#include "../minishell.h"

void adjust_var_bag(t_var_bag *bag, char c ,int i)
{       
        bag->slash_flag += (c == 92) ? 1:0;
        bag->slash_flag %= 2;
        bag->slash_flag *= (bag->spec_char == '\'' && bag->brack_flag) ? 0 : 1;
        if ((c == bag->spec_char || !bag->brack_flag) && !bag->slash_flag)
        {   if (c == '\'' || c == '"')
            {
                bag->spec_char = c;
                bag->brack_flag = (bag->brack_flag + 1) % 2;
            }
        }
        bag->slash_flag *= (c != 92) ? 0 : 1;
}

char **list_to_array(t_list *list)
{

    char **tab;
    int i;
    tab = malloc(sizeof(char **) * (ft_lstsize(list) + 1));
    i = 0;
    while (list)
    {
        tab[i++] = ft_strdup((char*)list->content);
        list = list->next;
    }
    tab[i] = NULL;
    return tab;
}

void free_array(void **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}
// todo
void free_struct_file(void *red)
{
    char *temp;

    temp = ((t_redirection*)red)->file;
    if (temp)
        free(temp);
    free(red);
}

void free_command(t_command *command)
{
    //free(command->command);
    if (command->in_redx)
        ft_lstclear(&(command->in_redx),&free_struct_file);
    if (command->out_redx)
        ft_lstclear(&(command->out_redx), &free_struct_file);
    ft_lstclear(&(command->args), &free);
}

void free_command_array(t_command **commands)
{
    int i;
    int j;
    
    i = 0;
    while (i < g_big_comm)
    {   
        g_small_comm = commands[i][0].test;
        j = 0;
        while(j < g_small_comm)
        {
            free_command(&((commands)[i][j]));
            j++;
        }
        free(commands[i]);
        i++;
    }
    free(commands);
}
