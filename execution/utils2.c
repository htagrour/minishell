/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:20:35 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/12 15:22:13 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"
    
int	ft_strchr_n(const char *s, int c)
{
	int j = 1;
	
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
    int i = lenght(args);
    while (i > 0)
    {
	    if (!strncmp(*args, "-n", 2))
        {
            if (!ft_strchr_n(*args, 'n'))
                *flag += 1;
        }
        else
            break;
        args++;
        i--;
    }
}

int		lenght(char **str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}