#include "../minishell.h"

// simple splite using ; as delimetor
int parse(char *line, t_command ***commands)
{
    int value = 1;
    int i;
    char **temp1;
    char **temp2;
    int elem_number;
    int j = 0;

    
    elem_number = 0;
    i = 0;
    //splitting by ; and get main commnds
    temp1 = updated_split(line, ';', &elem_number);
    *commands = malloc(sizeof(t_command*) * (elem_number + 1));
    // splitting by | and get sub command
    while (temp1[i])
    {
        j = -1;
        //geting subcommand
        temp2 = updated_split(temp1[i], '|', &elem_number);
        (*commands)[i] = malloc(sizeof(t_command) * (elem_number + 1));
        while (temp2[++j])
            ft_get_args((*commands)[j], temp2[j]);
        free_array((void**)temp2);
        i++;
    }
    free_array((void**)temp1);
    return value;
}