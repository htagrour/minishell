/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:30:20 by htagrour          #+#    #+#             */
/*   Updated: 2021/01/08 16:28:56 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		get_word_number(char const *str, char del)
{
	int		i;
	int		space_flag;
	int		words_number;
	int		spec1;
	char 	prev;
	char		spec_char;


	words_number = 0;
	spec1 = 0;

	spec_char = ' ';
	space_flag = 1;
	i = 0;
	prev = ' ';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && prev != 92)
		{
			spec1 += (str[i] != spec_char) ? 1: 0;
			spec_char = (!spec1) ? str[i] : spec_char;
			spec1 %= 2;
		}

		if (str[i] == del && !spec1)
			space_flag = 1;
		else
		{
			words_number += space_flag;
			space_flag = 0;
		}
		prev = str[i];
		i++;
	}
	return (words_number);
}

 static char **get_tokens(const char *str, int wnb, int del)
 {
 	char **tab;
 	int i;
 	int j;
 	int len;
	int spec1;
	int spec_char;
	char prev;



 	i = 0;
 	j = 0;
	spec1 =0;
	spec_char = ' ';
	prev = ' ';
 	if (!(tab = malloc(sizeof(char*) * (wnb + 1))))
 		return NULL;
 	while (str[i])
 	{
		 while (str[i] == del)
		 	i++;
		len = 0;
		if (str[i])
		{
			while(str[len + i] && !(str[len + i] == del && !spec1))
			{
				if ((str[len + i] == '\'' || str[len + i] == '"') &&  prev != 92)
				{
					spec1 += (str[i + len] != spec_char) ? 1: 0;
					spec_char = (!spec1) ? str[i + len] : spec_char;
					spec1 %= 2;
				}
				prev = str[len + i];
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
