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

int free_hash_map(t_hash_map *hm)
{
    t_listo *temp;
    t_listo *temp1;

    while (--hm->size >= 0)
    {
        temp = hm->item[hm->size];
        while (temp)
        {   
            temp1 = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            temp = temp1;
        }
        hm->item[hm->size] = NULL;
    }
    free(hm->item);
    free(hm);
    return 1;
}

unsigned int hash(const char *str,int size)
{
    unsigned int hash;

    hash = 0;
    while (str && *str)
    {
        hash = (hash + *str) % size;
        str++;  
    }
    return hash;
    
}


t_hash_map *init_hash_map(int size)
{
    t_hash_map *hm;

    if (!(hm = malloc(sizeof(t_hash_map))))
        return (NULL);
    hm->item = malloc(sizeof(t_listo*) * size);
    if (hm->item == NULL)
       return NULL;
    bzero(hm->item, sizeof(t_listo*) * size);
    hm->size = size;
    hm->elem_total = 0;
    return (hm);
}
