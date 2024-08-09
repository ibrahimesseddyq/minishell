/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:55:33 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/09 12:58:10 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

t_lst	*ft_lstadd_new_env(char *key, char *value)
{
	t_lst	*index;

	index = (t_lst *)malloc(sizeof(t_lst));
	if (!index)
		return (NULL);
	index->key = key;
    index->value = value;
	index->next = NULL;
	return (index);
}
