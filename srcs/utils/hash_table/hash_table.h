/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:39:35 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/19 19:06:22 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"

# define HASH_SIZE 120

typedef struct s_listo
{
	char			*key;
	char			*value;
	struct s_listo	*next;
}				t_listo;

typedef struct s_hash_map
{
	int		size;
	int		elem_total;
	t_listo	**item;
}				t_hash_map;

unsigned int	hash(const char *str, int size);
t_hash_map		*init_hash_map(int size);
char			*get_value(const char *key, t_hash_map *hm);
void			set_value(const char *key, const char *value, t_hash_map *hm);
int				free_hash_map(t_hash_map *hm);
void			delet_value(const char *key, t_hash_map *hm);
char			**hash_to_arr(t_hash_map *hm, int flag);
char			**sorted_key(t_hash_map *hm);
void			bubblesort(char **tab, int len);
void			key_value(char *key, char *value, char **dist, int *i);

#endif
