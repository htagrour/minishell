/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:58 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:25 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_bin(char *cmd, struct stat st, t_hash_map *env, int i)
{
	char	*temp1;
	char	**temp;
	char	*path;

	path = get_value("PATH", env);
	if (path[0])
	{
		temp = ft_split(path, ':');
		free(path);
		while (temp[++i])
		{
			temp1 = temp[i];
			temp[i] = ft_add_char(temp[i], '/');
			free(temp1);
			temp1 = ft_strjoin(temp[i], cmd);
			if (!stat(temp1, &st) && (st.st_mode & S_IXUSR))
				return (temp1);
			free(temp1);
		}
		free_array((void**)temp);
	}
	else
		free(path);
	return (NULL);
}

int	get_full_path(t_command *command, t_hash_map *env)
{
	char		*cmd;
	char		*bin;
	struct stat	st;

	if (!command->args)
		return (1);
	cmd = (char *)command->args->content;
	if (!cmd[0])
		return (127);
	if (is_built_in(cmd))
		return (0);
	if (!stat(cmd, &st) && !S_ISDIR(st.st_mode) && (st.st_mode & S_IXUSR))
		return (0);
	bin = get_bin(cmd, st, env, -1);
	if (!bin)
		return (127);
	free(command->args->content);
	command->args->content = (void *)ft_strdup(bin);
	free(bin);
	return (0);
}

int	get_in_fd(t_command command, int *last_fd)
{
	t_list	*temp;
	t_redx	*red;
	int		fd;

	fd = *last_fd;
	temp = command.in_redx;
	while (temp)
	{
		red = (t_redx*)temp->content;
		fd = open(red->file, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (*last_fd)
			close(*last_fd);
		*last_fd = fd;
		temp = temp->next;
	}
	return (0);
}

int	get_out_fd(t_command command, int *out_fd)
{
	t_list	*temp;
	int		fd;
	t_redx	*red;

	fd = *out_fd;
	temp = command.out_redx;
	while (temp)
	{
		red = (t_redx*)temp->content;
		if (red->type)
			fd = open(red->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd = open(red->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		if (*out_fd != 1)
			close(*out_fd);
		*out_fd = fd;
		temp = temp->next;
	}
	return (0);
}
