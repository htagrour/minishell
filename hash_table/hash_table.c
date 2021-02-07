#include "hash_table.h"
#include "../minishell.h"

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

t_listo *new_item(const char *key, const char *value)
{
    t_listo *item;

    if (!(item = malloc(sizeof(t_listo))))
        return (NULL);
    item->key = strdup(key);
    item->value = strdup(value);
    item->next = NULL;

    return (item);
}

int set_value(const char *key, const char *value, t_hash_map *hm)
{
    t_listo *temp;
    t_listo *item;

    temp = hm->item[hash(key,hm->size)];
    if (temp)
    {
        while (temp)
        {
            if (!strcmp(key, temp->key))
                break;
            temp = temp->next;
        }
        if (!temp)
        {
            item = new_item(key, value);
            item->next = hm->item[hash(key,hm->size)];
            hm->item[hash(key,hm->size)] = item;
            hm->elem_total += 1;
        }else
        {
            free(temp->value);
            temp->value = strdup(value);
        }
    }else
    {
        item = new_item(key, value);
        hm->item[hash(key,hm->size)] = item;
        hm->elem_total += 1;
    } 
    return 1;
}

char *get_value(const char *key, t_hash_map *hm)
{
    t_listo *temp;
    char *value;
    temp = hm->item[hash(key, hm->size)];
    while (temp)
    {
        if (!strcmp(key, temp->key))
            break;
        temp = temp->next;
    }
    if (!temp)
        value = strdup("");
    else
        value = strdup(temp->value);
    return (value);
}
int delet_value(const char *key, t_hash_map *hm)
{
    t_listo *temp;
    t_listo *prev;
    int hash_code;

    hash_code = hash(key, hm->size);
    temp = hm->item[hash_code];
    prev = NULL;
    while(strcmp(key, temp->key) && temp->next)
    {
        prev = temp;
        temp = temp->next;
    }

    if (!strcmp(key, temp->key))
    {
        if (prev)
            prev->next = temp->next;
        else
            hm->item[hash_code] = temp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        hm->elem_total -= 1; 
    }
    return 1;
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
