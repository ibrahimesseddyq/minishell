/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/30 11:40:08 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"


void	set_env(t_lst *lst, char *key, char *new_value)
{
	t_lst *new;
	t_lst *tmp;

	new = NULL;
	tmp = lst;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			lst->value = new_value;
			return ;
		}
		lst = lst->next;
	}
	lst = tmp;
	new = ft_lstadd_new_env(key, new_value);
	ft_lstadd_back_env(&lst, new);
}
