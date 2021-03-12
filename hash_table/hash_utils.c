#include "hash_table.h"

char **hash_to_arr(t_hash_map *hm)
{
    char **tab;
    t_listo *temp;
    int i;
    int size;
    char *temp1;

    i = 0;
    size = hm->size;
    tab = malloc(sizeof(char*) * (hm->elem_total + 1));
    if (!tab)
        return (NULL);
    while (--size >= 0)
    {
        temp = hm->item[size];
        while (temp)
        {   
            temp1 = ft_strjoin(temp->key, "=");
            tab[i++] = ft_strjoin(temp1, temp->value);
            free(temp1);
            temp = temp->next;
        } 
    }
    tab[i] = NULL;
    return tab;
}

