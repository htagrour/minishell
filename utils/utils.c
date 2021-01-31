#include "../minishell.h"

void adjust_var_bag(t_var_bag *bag, char c ,int i)
{       
        bag->slash_flag += (c == 92) ? 1:0;
        bag->slash_flag %= 2;
		if ((c == '\'' || c == '"') && !bag->slash_flag)
		{
			bag->brack_flag += (c != bag->spec_char) ? 1: 0;
			bag->spec_char = (!bag->brack_flag) ? c : bag->spec_char;
			bag->brack_flag %= 2;
		}
        bag->slash_flag *= (c != 92) ? 0 : 1;
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
void free_command(t_command *command)
{
    free(command->command);
    ft_lstclear(&(command->in_redx),&free);
    ft_lstclear(&(command->out_redx), &free);
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
        while(i < g_small_comm)
        {
            free_command(&((commands)[i][j]));
            //ft_bzero(&commands[i][j], sizeof(t_command));
            free(&commands[i][j]);
            j++;
        }
        i++;
    }
    free(*commands);
}