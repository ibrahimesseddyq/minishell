/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:55:33 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/28 14:39:36 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstadd_new_env(char *key, char signe, char *value)
{
	t_lst	*index;

	index = (t_lst *)malloc(sizeof(t_lst));
	if (!index)
		return (NULL);
	index->key = key;
	index->signe = signe;
    index->value = value;
	index->next = NULL;
	return (index);
}
