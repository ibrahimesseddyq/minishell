/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:55:33 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/22 21:29:07 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

t_lst *ft_lstadd_new_env(char *key, char *value, char signe)
{
	t_lst *index;

	index = (t_lst *)gcalloc(sizeof(t_lst));
	if (!index)
		return (NULL);
	index->key = key;
	index->signe = signe;
	index->value = value;
	index->next = NULL;
	index->set = 1;
	return (index);
}
