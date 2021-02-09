#include "../minishell.h"

int process_line(char *line, t_hash_map *hm)
{
    int i;
    char **temp1;
    char **temp2;
    int j = 0;
    t_command *command;
    int last_fd = 0;
    i = 0;
    temp1 = updated_split(line, ';', &g_big_comm);
    while (temp1[i])
    {
        j = -1;
        temp2 = updated_split(temp1[i], '|', &g_small_comm);
        //if (g_small_comm == 1)
            //exec builtin function
            //j+= exec;
        while (temp2[++j])
        {
            command = malloc(sizeof(t_command));
            ft_bzero(command, sizeof(t_command));
            get_cmd(command, temp2[j], hm);
            execute_cmd(*command, &last_fd, (temp2[j + 1] != NULL), hm);
            free_command(command);
        }
        //print errors
        free_array((void**)temp2);
        i++;
    }
    free_array((void**)temp1);
    return 1;
}
