/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:12:16 by ibes-sed          #+#    #+#             */
/*   Updated: 2023/11/12 00:13:07 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*index;
	t_list	*temp;

	if (!lst || !del)
		return ;
	index = (*lst);
	while (index)
	{
		temp = index->next;
		ft_lstdelone(index, del);
		index = temp;
	}
	*lst = NULL;
}
