/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:32:50 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 16:10:43 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "../../../minishell.h"

t_listo	*new_item(const char *key, const char *value)
{
	t_listo	*item;

	item = malloc(sizeof(t_listo));
	if (!item)
		return (NULL);
	item->key = ft_strdup(key);
	item->value = ft_strdup(value);
	item->next = NULL;
	return (item);
}

void	add_new_key(const char *key, const char *value,
	t_hash_map *hm, int alone)
{
	t_listo	*item;

	item = new_item(key, value);
	if (!alone)
		item->next = hm->item[hash(key, hm->size)];
	hm->item[hash(key, hm->size)] = item;
	hm->elem_total += 1;
}

void	set_value(const char *key, const char *value, t_hash_map *hm)
{
	t_listo	*temp;

	temp = hm->item[hash(key, hm->size)];
	if (temp)
	{
		while (temp)
		{
			if (!strcmp(key, temp->key))
				break ;
			temp = temp->next;
		}
		if (!temp)
			add_new_key(key, value, hm, 0);
		else
		{
			if (value)
			{
				free(temp->value);
				temp->value = ft_strdup(value);
			}
		}
	}
	else
		add_new_key(key, value, hm, 1);
}

char	*get_value(const char *key, t_hash_map *hm)
{
	t_listo	*temp;
	char	*value;

	temp = hm->item[hash(key, hm->size)];
	while (temp)
	{
		if (!strcmp(key, temp->key))
			break ;
		temp = temp->next;
	}
	if (!temp)
		value = ft_strdup("");
	else
		value = ft_strdup(temp->value);
	return (value);
}

void	delet_value(const char *key, t_hash_map *hm)
{
	t_listo	*temp;
	t_listo	*prev;
	int		hash_code;

	hash_code = hash(key, hm->size);
	temp = hm->item[hash_code];
	prev = NULL;
	if (!temp)
		return ;
	while (strcmp(key, temp->key) && temp->next)
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
}
