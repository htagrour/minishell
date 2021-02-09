#include "../minishell.h"


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

    temp = ((t_redx*)red)->file;
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
