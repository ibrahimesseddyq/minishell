/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:14:48 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/08/15 18:31:07 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*index;

	index = (t_list *)gcalloc(sizeof(t_list));
	if (!index)
		return (NULL);
	index -> content = content;
	index -> next = NULL;
	return (index);
}
