/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/13 15:34:51 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int get_symbol_exist(char *str, char symbol)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == symbol)
			return (1);
		i++;
	}
	return (0);
}
void ft_export(char *str, t_lst *lst)
{
	int exist;
	char **str_split;

	exist = get_symbol_exist(str, '=');
	if(exist)
	{
		str_split = ft_split(str, '=');
		if(!str_split)
			return ;
		set_env(lst, str_split[0], str_split[1]);
	}
	else
	{
		set_env(lst, str, "");
	}
}
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
