#include "hash_table.h"
#include <string.h>

unsigned int hash(const char *str,int size)
{
    unsigned int hash;

    hash = 0;
    while (str && *str)
    {
        hash = (hash + *str) % size;
        str++;  
    }
    
}

t_hash_map *init_hash_map(int size)
{
    t_hash_map *hm;

    if (!(hm = malloc(sizeof(hm))))
        return (NULL);
    hm->size = size;
    hm->item = (t_list**)malloc(sizeof(t_list) * size);
    if (!hm->item)
        return NULL;
    bzero(hm->item, sizeof(hm->item));
    return (hm);
}

t_list *new_item(const char *key, const char *value)
{
    t_list *item;

    if (!(item = malloc(sizeof(item))))
        return (NULL);
    item->key = strdup(key);
    item->value = strdup(value);
    item->next = NULL;

    return (item);
}

int set_value(const char *key, const char *value, t_hash_map *hm)
{
    t_list *temp;
    t_list *item;

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
        }else
        {
            free(temp->value);
            temp->value = strdup(value);
        }
    }else
    {
        item = new_item(key, value);
        hm->item[hash(key,hm->size)] = item;
    } 
    return 1;
}

char *get_value(const char *key, t_hash_map *hm)
{
    t_list *temp;
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

int free_hash_map(t_hash_map *hm)
{
    t_list *temp;
    t_list *temp1;
    while (--hm->size)
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
    }
    free(hm);
    return 1;
}
