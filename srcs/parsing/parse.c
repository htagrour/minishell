/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:28:53 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:55 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*get_commands(char **temp, int total, t_hash_map *env)
{
	t_command	*commands;
	int			i;

	commands = (t_command*) malloc(sizeof(t_command) * (total));
	if (!commands)
		return (NULL);
	i = -1;
	while (temp[++i])
	{
		if (get_cmd(&commands[i], temp[i], env))
		{
			free_array((void**)temp);
			free_command_array(commands, total);
			return (NULL);
		}
		commands[i].next = (temp[i + 1] != NULL);
		free(temp[i]);
	}
	free(temp);
	return (commands);
}
