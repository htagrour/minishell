/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:28:10 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:31 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strchr_n(const char *s, int c)
{
	int	j;

	j = 2;
	while (s[j])
	{
		if (s[j] != (char)c)
			return (1);
		j++;
	}
	return (0);
}

int	ft_strchr_eql(const char *s, int c)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] == (char)c)
			return (j);
		j++;
	}
	return (j);
}

void	echo_check_n(char **args, int *flag)
{
	int	i;

	i = array_lenght(args);
	while (i > 0)
	{
		if (!strncmp(*args, "-n", 2))
		{
			if (!ft_strchr_n(*args, 'n'))
				*flag += 1;
			else
				break ;
		}
		else
			break ;
		args++;
		i--;
	}
}

int	array_lenght(char **str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

void	add_return(t_hash_map *env, int ret)
{
	char	*temp;

	temp = ft_itoa(ret);
	set_value("?", temp, env);
	free(temp);
}
