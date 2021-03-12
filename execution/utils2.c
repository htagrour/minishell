/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:20:35 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/12 03:09:35 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
    
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

void	echo_check_n(char *args, int *flag)
{
	    if (!strncmp(args, "-n", 2))
        {
            if (!ft_strchr_n(args, 'n'))
                *flag += 1;
        }
}

// int		lenght(char **str)
// {
// 	int	n;

// 	n = 0;
// 	while (str[n])
// 		n++;
// 	return (n);
// }