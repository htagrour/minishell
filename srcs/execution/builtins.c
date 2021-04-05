/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 08:54:07 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:18 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(char **args, t_hash_map *env)
{
	char	**envs;
	int		i;

	args++;
	if (!*args)
	{
		envs = hash_to_arr(env, 0);
		i = -1;
		while (envs[++i])
			if (*envs[i])
				ft_putendl_fd(envs[i], STDOUT_FILENO, 1);
		free_array((void**)envs);
		return (0);
	}
	else
		return (print_error("env don't accept args", 1, env));
}

int	exit_(t_command cmd, t_hash_map *env)
{
	t_list	*temp;

	temp = cmd.args->next;
	if (!temp)
	{
		ft_putendl_fd("exit", STDOUT_FILENO, 1);
		exit(ft_atoi(get_value("?", env)));
	}
	if (!is_valide_exit((char *)temp->content))
		exit(print_error("exit: numeric argument required", 255, env));
	if (temp->next)
		return (print_error("exit: too many arguments", 1, env));
	if (!cmd.next)
		ft_putendl_fd("exit", STDOUT_FILENO, 1);
	exit(ft_atoi((char*)temp->content));
	return (0);
}

int	echo(char **args)
{
	int	flag;

	flag = 0;
	args++;
	if (*args)
	{
		echo_check_n(args, &flag);
		if (flag)
			args += flag;
		while (*args)
		{
			ft_putstr_fd(*args, STDOUT_FILENO);
			if (*(args + 1))
				ft_putstr_fd(" ", STDOUT_FILENO);
			args++;
		}
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	unset(t_command command, t_hash_map *env)
{
	t_list	*temp;
	char	*key;

	temp = command.args->next;
	while (temp)
	{
		key = (char*)temp->content;
		if (is_valide_key(key))
			delet_value(key, env);
		else
			print_error("not valide identifier", 1, env);
		temp = temp->next;
	}
	return (0);
}

int	export(t_command command, t_hash_map *env, int out_fd)
{
	t_list	*temp;
	int		ret;

	temp = command.args->next;
	if (!temp)
		return (print_env(env, out_fd));
	while (temp)
	{
		ret = add_env((char *)temp->content, env);
		temp = temp->next;
	}
	return (ret);
}
