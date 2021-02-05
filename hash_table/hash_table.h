#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_SIZE 100

#include <stdlib.h>
typedef struct  s_list
{
    char *key;
    char *value;
    struct s_list *next;
} t_list;

typedef struct s_hash_map
{
    int size;
    t_list **item;
}t_hash_map;


unsigned int  hash(const char *str, int size);
t_hash_map *init_hash_map(int size);
char *get_value(const char *key, t_hash_map *hm);
int set_value(const char *key, const char *value, t_hash_map *hm);
int free_hash_map(t_hash_map *hm);

#endif