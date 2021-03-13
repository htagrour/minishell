/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:30:20 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/08 18:34:31 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		get_word_number(char const *str, char del, int *wn)
{
	int			del_flag;
	t_var_bag	bag;

	ft_bzero(&bag, sizeof(bag));
	*wn = 0;
	del_flag = 1;
	while (*str)
	{
		while(*str == ' ' && !bag.brack_flag)
			str++;
		if (*str)
		{
			if (*str == del && !bag.brack_flag && !bag.slash_flag)
			{
				if (del_flag)
					return (-1);
				del_flag = 1;
			}
			else
			{
				*wn += del_flag;
				del_flag = 0;
			}
			adjust_var_bag(&bag, *str);
			str++;
		}
	}
	if (bag.brack_flag || (del_flag && del == '|'))
		return (-1);
	return (*wn);
}

static char		**get_tokens(const char *str, int wnb, int del)
{
	char		**tab;
	int			i;
	int			j;
	int			len;
	t_var_bag	bag;

	ft_bzero(&bag, sizeof(bag));
	i = 0;
	j = 0;
	if (!(tab = malloc(sizeof(char*) * (wnb + 1))))
		return (NULL);
	while (*str != '\0')
	{
		len = 0;
		while(*str == del)
			str++;
		if (*str)
		{
			while (*(str + len) && !(*(str + len) == del && !bag.brack_flag && !bag.slash_flag))
			{
				adjust_var_bag(&bag, *(str +len));
				len++;
			}
			tab[j] = ft_substr(str, 0,len);
			j++;
			str += (len);
		}
	}
	tab[j] = NULL;
	return (tab);
}

char			**updated_split(char const *str, char del, int *ele_number)
{
	if (!str)
		return (NULL);
	*ele_number = get_word_number(str, del, ele_number);
	if (*ele_number < 0)
		return (NULL);
	return (get_tokens(str, *ele_number, del));
}
