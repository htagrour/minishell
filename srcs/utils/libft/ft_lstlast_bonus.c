/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 09:11:11 by htagrour          #+#    #+#             */
/*   Updated: 2021/03/18 10:18:37 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *list)
{
	t_list	*current_ele;

	current_ele = list;
	if (!current_ele)
		return (current_ele);
	while (current_ele->next)
		current_ele = current_ele->next;
	return (current_ele);
}
