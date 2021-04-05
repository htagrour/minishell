/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:45 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:37 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	change_dir(t_command command, char **path, char **old_path, t_hash_map *env)
{
	char	*temp;

	if (command.args->next)
	{
		temp = (char*) command.args->next->content;
		if (!strcmp(temp, "-"))
			*path = get_value("OLDPWD", env);
		else
		{
			if (temp[0] == '~')
				*path = ft_strjoin("/Users/fsarbout", temp + 1);
			else
				*path = ft_strdup(temp);
		}
	}
	else
		*path = ft_strdup("/Users/fsarbout");
	*old_path = getcwd(NULL, 1024);
	if (chdir(*path) != 0)
		return (print_error("PATH not exist or a file", 1, env));
	free(*path);
	*path = getcwd(NULL, 1024);
	return (0);
}

int	cd(t_command command, t_hash_map *env)
{
	char	*path;
	char	*old_path;

	if (!change_dir(command, &path, &old_path, env))
	{
		set_value("OLDPWD", old_path, env);
		set_value("PWD", path, env);
	}
	free(path);
	free(old_path);
	return (0);
}

int	pwd(void)
{
	char	*current_path;

	current_path = getcwd(NULL, 1024);
	ft_putendl_fd(current_path, STDOUT_FILENO, 1);
	free(current_path);
	return (0);
}

int	built_in1(t_command command, t_hash_map *env, int flag)
{
	char	*cmd;
	int		res;
	int		out_fd;

	out_fd = STDOUT_FILENO;
	cmd = (char*)command.args->content;
	if (cmd)
	{
		res = is_buitin1(cmd);
		if (res == -1)
			return (-1);
	}
	if (flag)
		if (get_in_fd(command, &out_fd) || get_out_fd(command, &out_fd))
			return (print_error("FIle ERROR", 1, env));
	if (res == 1)
		return (cd(command, env));
	if (res == 2)
		return (export(command, env, out_fd));
	if (res == 3)
		return (unset(command, env));
	if (res == 4)
		return (exit_(command, env));
	return (-1);
}

int	built_in2(char **args, t_hash_map *envs)
{
	int	res;

	res = -1;
	if (!strcmp(*args, "echo"))
		res = echo(args);
	if (!strcmp(*args, "pwd"))
		res = pwd();
	if (!strcmp(*args, "env"))
		res = env(args, envs);
	return (res);
}
