/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:45:29 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 16:01:13 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void	free_struct_file(void *red)
{
	char	*temp;

	temp = ((t_redx*)red)->file;
	if (temp)
		free(temp);
	free(red);
}

void	free_command(t_command *command)
{
	if (command->in_redx)
		ft_lstclear(&(command->in_redx), &free_struct_file);
	if (command->out_redx)
		ft_lstclear(&(command->out_redx), &free_struct_file);
	ft_lstclear(&(command->args), &free);
}

int	free_command_array(t_command *commands, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		free_command(&commands[i]);
		i++;
	}
	free(commands);
	return (-1);
}
