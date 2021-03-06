/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:04:37 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/18 10:27:24 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *des, const void *src, size_t n)
{
	unsigned char		*des1;
	const unsigned char	*src1;

	if (!des && !src)
		return (NULL);
	if (des == src)
		return (des);
	des1 = des;
	src1 = src;
	while (n--)
	{
		*des1++ = *src1++;
	}
	return (des);
}
