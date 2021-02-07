#include "../minishell.h"

// simple splite using ; as delimetor

t_command **parse(char *line, t_hash_map *hm)
{
    t_command **commands;
    int i;
    char **temp1;
    char **temp2;
    int j = 0;

    
    i = 0;
    //splitting by ; and get main commnds
    temp1 = updated_split(line, ';', &g_big_comm);
    commands = (t_command**)malloc(sizeof(t_command**) * (g_big_comm + 1));
    ft_bzero(commands, sizeof(t_command**));
    // splitting by | and get sub command
    while (temp1[i])
    {
        j = -1;
        //geting subcommand
        temp2 = updated_split(temp1[i], '|', &g_small_comm);
        commands[i] = malloc(sizeof(t_command) * (g_small_comm));
        while (temp2[++j])
        {
	        ft_bzero(&commands[i][j], sizeof(t_command));
            commands[i][j].test = g_small_comm;
            ft_get_args(&commands[i][j], temp2[j], hm);
            //may be i should put execution part here
        }
        free_array((void**)temp2);
        i++;
    }
    free_array((void**)temp1);
    return commands;
}
