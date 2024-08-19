/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:55:44 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/18 05:44:34 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstadd_back_env(t_lst **lst, t_lst *new)
{
    t_lst *temp;

    if (new == NULL)
        return;
    
    new->next = NULL;  // Ensure the new node's next pointer is NULL
    
    if (*lst == NULL)
    {
        *lst = new;
    }
    else
    {
        temp = *lst;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}
