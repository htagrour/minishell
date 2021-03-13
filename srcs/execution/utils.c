/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:28:10 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/13 16:57:54 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strchr_n(const char *s, int c)
{
	int j = 2;
	
	while (s[j])
	{
        
        if (s[j] != (char)c)
            return (1);
		j++;
	}
    return (0);
}

void	echo_check_n(char **args, int *flag)
{ 
    int i = array_lenght(args);

    while (i > 0)
    {
	    if (!strncmp(*args, "-n", 2))
        {
            if (!ft_strchr_n(*args, 'n'))
                *flag += 1;
            else
                break;
        }
        else
            break;
        args++;
        i--;
    }
}

int		array_lenght(char **str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}