#include "../../includes/minishell.h"


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

int    print_error(char *str, int error, t_hash_map *env)
{
    char *temp;
    temp = ft_itoa(error);
    ft_putendl_fd(str, STDOUT_FILENO);
    set_value("?", temp, env);
    free(temp);
    errno = error;
    return (error);
}

int free_array(void **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
    return (-1);
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
    if (command->in_redx)
        ft_lstclear(&(command->in_redx),&free_struct_file);
    if (command->out_redx)
        ft_lstclear(&(command->out_redx), &free_struct_file);
    ft_lstclear(&(command->args), &free);
}

int free_command_array(t_command *commands,int total)
{
    int i;
    
    i = 0;
    while(i < total)
    {
        free_command(&commands[i]);
        i++;
    }
   free(commands);
   return (-1);
}
