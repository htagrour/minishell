#include "../minishell.h"

// simple splite using ; as delimetor
int parse(char *line)
{
    int value;
    char **commandes;
    int i = 0;
    value = 1;

    commandes = ft_split(line, ';');
    while (commandes[i])
    {
        printf("%s\n", commandes[i++]);
    }
    free_array((void**)commandes);
    return value;
}