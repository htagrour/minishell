/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:56:43 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:15 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valide_key(char *str)
{
	if (!ft_isalpha(*str))
		return (0);
	str++;
	while (*str)
	{
		if (!(ft_isalnum(*str)) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	is_valide_exit(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	add_env(char *str, t_hash_map *env)
{
	char	*key;
	int		i;
	int		index;

	i = 0;
	index = ft_strchr_eql(str, '=');
	key = ft_substr(str, 0, index);
	if (!is_valide_key(key))
	{
		free(key);
		return (print_error("not a valide identifier", 1, env));
	}
	if (str[index] != '=')
		set_value(key, NULL, env);
	else
		set_value(key, str + index + 1, env);
	free(key);
	return (0);
}

void	new_print(const char *str, int out_fd)
{
	while (*str)
	{
		if (belong("\\$\"", *str))
			ft_putchar_fd('\\', out_fd);
		ft_putchar_fd(*str, out_fd);
		str++;
	}	
}

int	print_env(t_hash_map *env, int out_fd)
{
	char	*value;
	int		i;
	char	**keys;

	i = 0;
	keys = sorted_key(env);
	while (keys[i])
	{
		ft_putendl_fd("declare -x ", out_fd, 0);
		ft_putendl_fd(keys[i], out_fd, 0);
		value = get_value(keys[i], env);
		if (value)
		{
			ft_putstr_fd("=\"", out_fd);
			new_print(value, out_fd);
			ft_putchar_fd('\"', out_fd);
			free(value);
		}
		ft_putchar_fd('\n', out_fd);
		i++;
	}
	free_array((void**)keys);
	return (0);
}
