/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:20:45 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/18 10:26:08 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *des, const void *src, int c, size_t n)
{
	unsigned char		*des1;
	const unsigned char	*src1;

	if (des != src)
	{
		des1 = des;
		src1 = src;
	}
	while (n--)
	{
		*des1++ = *src1++;
		if ((unsigned char)c == *src1)
		{
			*des1++ = *src1;
			return ((void*)(des1));
		}
	}
	return (NULL);
}
