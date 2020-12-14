#include "minishell.h"


int main (void)
{
    char *line;
    int i = 1;
	while(i > 0)
	{
        i  = get_next_line(1, &line);
        parse(line);
        free(line);
	} 
    return 0;
}
