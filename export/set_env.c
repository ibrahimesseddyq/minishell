/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/20 06:13:50 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	choose_set_env(t_lst *lst, char *new_value, int sign)
{
	if (new_value)
	{
		lst->value = ft_strdup(new_value);
		lst->set = 1;
		if (sign)
			lst->signe = '=';
	}
	else
	{
		lst->set = 0;
		lst->value = ft_strdup("");
		lst->key = ft_strdup("");
	}
}

void	set_env(t_lst *lst, char *key, char *new_value, int sign)
{
	t_lst	*new;
	t_lst	*tmp;

	new = NULL;
	tmp = lst;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			choose_set_env(lst, new_value, sign);
			return ;
		}
		lst = lst->next;
	}
	lst = tmp;
	new = choose_add_set_env(key, new_value, sign);
	ft_lstadd_back_env(&lst, new);
}

void	ft_export(char **str, t_lst *lst)
{
	int		i;

	i = 1;
	if (!str[1])
		print_export(lst);
	else
	{
		while (str[i])
		{
			printf("[ft_export] str [%s]\n", str[i]);
			export_var(str, lst, i);
			i++;
		}
	}
	if (ft_exit(1, GET_EXIT_STATUS) == 257)
		ft_exit(1, SET_EXIT_STATUS);
}
