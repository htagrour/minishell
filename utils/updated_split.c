/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:30:20 by htagrour          #+#    #+#             */
/*   Updated: 2021/01/30 17:23:55 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		get_word_number(char const *str, char del)
{
	int		i;
	int		del_flag;
	int		words_number;

	t_var_bag bag;

	ft_bzero(&bag, sizeof(bag));
	words_number = 0;
	del_flag = 1;
	i = 0;
	while (str[i])
	{	
		if (str[i] == del && !bag.brack_flag)
			del_flag = 1;
		else
		{
			words_number += del_flag;
			del_flag = 0;
		}
		adjust_var_bag(&bag, str[i], i);
		i++;
	}
	if (bag.brack_flag)
		printf("ERROR\n");
	
	return (words_number);
}

 static char **get_tokens(const char *str, int wnb, int del)
 {
 	char **tab;
 	int i;
 	int j;
 	int len;
	t_var_bag bag;

	ft_bzero(&bag, sizeof(bag));
 	i = 0;
 	j = 0;

 	if (!(tab = malloc(sizeof(char*) * (wnb + 1))))
 		return NULL;
 	while (str[i])
 	{
		 while (str[i] == del)
		 	i++;
		len = 0;
		if (str[i])
		{
			while(str[len + i] && !(str[len + i] == del && !bag.brack_flag))
			{
				adjust_var_bag(&bag, str[len+i], i);
				len++;
			}
			tab[j] = malloc(sizeof(char) * (len + 1));
			ft_strlcpy(tab[j], str + i, len + 1);
			i += len;
			j++;
		}
 	}
 	tab[j] = 0;
 	return tab;
 }

char			**updated_split(char const *str, char del, int *ele_number)
{
	if (!str)
		return (NULL);
	*ele_number = get_word_number(str, del);
	
	return (get_tokens(str, *ele_number, del));	
}
