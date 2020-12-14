#include "../minishell.h"
void free_array(void **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}