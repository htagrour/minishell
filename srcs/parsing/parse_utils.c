/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:28:42 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:51 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	adjust_var_bag(t_var_bag *bag, char c)
{
	if (c == 92)
		bag->slash_flag++;
	bag->slash_flag %= 2;
	if (bag->spec_char == '\'' && bag->brack_flag)
		bag->slash_flag = 0;
	if ((c == bag->spec_char || !bag->brack_flag) && !bag->slash_flag)
	{
		if (c == '\'' || c == '"')
		{
			bag->spec_char = c;
			bag->brack_flag = (bag->brack_flag + 1) % 2;
		}
	}
	if (c != 92)
		bag->slash_flag = 0;
}

int	belong(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	is_red(char c)
{
	return (c == '<' || c == '>');
}

int	conditions(char c, t_var_bag bag, char n)
{
	if (bag.brack_flag && bag.spec_char == '\'' && c != '\'')
		return (0);
	if (c == '"' && !bag.slash_flag)
		return (1);
	if (c == '\'' && (!bag.slash_flag
			&& !(bag.brack_flag && bag.spec_char == '"')))
		return (1);
	if (c == '\\')
	{
		if (bag.brack_flag && bag.spec_char == '"')
		{
			if (belong("$\"\\", n) && !bag.slash_flag)
				return (1);
		}
		else if (!bag.slash_flag)
			return (1);
	}
	return (0);
}

char	*get_env(char *str, char **ptr, int len, t_hash_map *hm)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(str, 0, len);
	temp2 = get_value(temp1, hm);
	*ptr = ft_strjoin(*ptr, temp2);
	free(temp1);
	free(temp2);
	return (NULL);
}
