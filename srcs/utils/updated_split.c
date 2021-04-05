/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:30:20 by htagrour          #+#    #+#             */
/*   Updated: 2021/04/05 16:01:03 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_condition(char c, t_var_bag *bag, int *wn, int *del_flag)
{
	if (c == bag->del && !bag->brack_flag && !bag->slash_flag)
	{
		if (*del_flag)
			return (-1);
		*del_flag = 1;
	}
	else
	{
		*wn += *del_flag;
		*del_flag = 0;
	}
	adjust_var_bag(bag, c);
	return (0);
}

static int	get_word_number(char const *str, char del, int *wn)
{
	int			del_flag;
	t_var_bag	bag;

	ft_bzero(&bag, sizeof(bag));
	*wn = 0;
	del_flag = 1;
	bag.del = del;
	while (*str)
	{
		while (*str == ' ' && !bag.brack_flag)
		{
			adjust_var_bag(&bag, *str);
			str++;
		}
		if (*str)
		{
			if (check_condition(*str, &bag, wn, &del_flag) == -1)
				return (-1);
			str++;
		}
	}
	if (bag.brack_flag || (del_flag && del == '|') || bag.slash_flag)
		return (-1);
	return (*wn);
}

int	add_token(const char *str, char **tab, t_var_bag *bag)
{
	int	j;
	int	len;

	j = 0;
	while (*str != '\0')
	{
		len = 0;
		while (*str == bag->del)
			str++;
		if (*str)
		{
			while (*(str + len) && !(*(str + len) == bag->del
						 && !bag->brack_flag && !bag->slash_flag))
			{
				adjust_var_bag(bag, *(str + len));
				len++;
			}
			tab[j] = ft_substr(str, 0, len);
			j++;
			str += (len);
		}
	}
	return (j);
}

static char	**get_tokens(const char *str, int wnb, int del)
{
	char		**tab;
	int			j;
	t_var_bag	bag;

	ft_bzero(&bag, sizeof(bag));
	bag.del = del;
	tab = malloc(sizeof(char *) * (wnb + 1));
	if (!tab)
		return (NULL);
	j = add_token(str, tab, &bag);
	tab[j] = NULL;
	return (tab);
}

char	**updated_split(char const *str, char del, int *ele_number)
{
	if (!str)
		return (NULL);
	*ele_number = get_word_number(str, del, ele_number);
	if (*ele_number < 0)
		return (NULL);
	return (get_tokens(str, *ele_number, del));
}
