/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:35:44 by htagrour          #+#    #+#             */
/*   Updated: 2021/04/03 14:54:49 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	tab = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}

char 	*ft_add_char(const char *str, char c)
{
	int		len;
	char	*tab;

	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	tab = malloc(sizeof(char) * len + 2);
	if (!tab)
		return (NULL);
	if (len)
		ft_strlcpy(tab, str, len + 1);
	tab[len++] = c;
	tab[len] = 0;
	return (tab);
}

char	*ft_del_char(const char *str)
{
	int		len;
	char	*tab;

	if (!*str)
		return (NULL);
	len = ft_strlen(str) - 1;
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, str, len + 1);
	tab[len] = 0;
	return (tab);
}
