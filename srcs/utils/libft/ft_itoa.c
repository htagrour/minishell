/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:55:21 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/19 19:08:56 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	number_digit(int n)
{
	if (!n)
		return (0);
	return (1 + number_digit(n / 10));
}

char	*ft_itoa(int n)
{
	int				len;
	char			*tab;
	unsigned int	a;

	if (n <= 0)
	{
		len = number_digit(n) + 1;
		a = n * -1;
	}
	else
	{
		len = number_digit(n);
		a = n;
	}
	tab = (char *)malloc(sizeof(char) * len + 1);
	tab[len] = '\0';
	while (--len >= 0)
	{
		tab[len] = a % 10 + '0';
		a /= 10;
	}
	if (n < 0)
		tab[0] = '-';
	return (tab);
}
