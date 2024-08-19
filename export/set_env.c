/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/19 00:42:49 by armanov          ###   ########.fr       */
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
void print_export(t_lst *lst)
{
	t_lst *head;

	head = lst;
	while(head)
	{
		if (head->signe != '=')
		{
			printf("declare -x %s\n",head->key);

		}
		else if(head->value)
		{
			printf("declare -x %s=\"%s\"\n",head->key, head->value);
		}
		else
			printf("declare -x %s=\"\"\n",head->key);

		head = head->next;
	}
}
void ft_export(char **str, t_lst *lst)
{
	int exist;
	char **str_split;
	int i;

	i = 1;

	if (!str[1])
	{
		print_export(lst);
	}
	else
	{
		while(str[i])
		{

			exist = get_symbol_exist(str[i], '=');
			if(exist)
			{
				str_split = ft_split(str[i], '=');
				if(!str_split)
					return ;
				set_env(lst, str_split[0], str_split[1], exist);
			}
			else
			{
				set_env(lst, str[i], "", exist);
			}
			i++;
		}
	}
}
void	set_env(t_lst *lst, char *key, char *new_value, int sign)
{
	t_lst *new;
	t_lst *tmp;

	new = NULL;
	tmp = lst;
	while (lst)
	{

		if (ft_strcmp(lst->key, key) == 0)
		{
			// printf("key1 %s key2 %s\nvalue1 %s value2 %s\n",key, lst->key,new_value, lst->value);
			if (new_value)
				lst->value = ft_strdup(new_value);
			else
				lst->value = ft_strdup("");


			return ;
		}
		lst = lst->next;
	}
	lst = tmp;
	if (sign)
		new = ft_lstadd_new_env(key, new_value, '=');
	else
		new = ft_lstadd_new_env(key, new_value, '\0');

	ft_lstadd_back_env(&lst, new);
}
