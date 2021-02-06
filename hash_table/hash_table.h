#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_SIZE 100

#include <stdlib.h>
#include "../minishell.h"
typedef struct  s_listo
{
    char *key;
    char *value;
    struct s_listo *next;
} t_listo;

typedef struct s_hash_map
{
    int size;
    int elem_total;
    t_listo **item;
}t_hash_map;


unsigned int  hash(const char *str, int size);
t_hash_map *init_hash_map(int size);
char *get_value(const char *key, t_hash_map *hm);
int set_value(const char *key, const char *value, t_hash_map *hm);
int free_hash_map(t_hash_map *hm);
int delet_value(const char *key, t_hash_map *hm);
char **hash_to_arr(t_hash_map *hm);

#endif