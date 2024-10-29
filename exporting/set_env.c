/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/29 10:29:51 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	choose_set_env(t_lst **lst, char *new_value, int sign)
{
	if (lst)
	{
		if (new_value)
		{
			(*lst)->value = ft_strdup(new_value);
			(*lst)->set = 1;
			if (sign)
				(*lst)->signe = '=';
			else
				(*lst)->signe = 0;
		}
		else
		{
			(*lst)->set = 0;
			(*lst)->value = ft_strdup("");
			(*lst)->key = ft_strdup("");
		}
	}
}

void	set_env(t_lst **lst, char *key, char *new_value, int sign)
{
	t_lst	*new;
	t_lst	*tmp;

	new = NULL;
	tmp = (*lst);
	printf("set env\n");
	if (lst)
	{
		while ((*lst))
		{
			if (ft_strcmp((*lst)->key, key) == 0)
			{
				choose_set_env(lst, new_value, sign);
				return ;
			}
			(*lst) = (*lst)->next;
		}
		(*lst) = tmp;
		new = choose_add_set_env(key, new_value, sign);
		ft_lstadd_back_env(lst, new);
	}
}

void	ft_export(char **str, t_lst *lst)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	if (!str[1])
		print_export(lst);
	else
	{
		while (str[i])
		{
			if (check_valid_export(str[i]) && str[i][0])
				export_var(str, &lst, i);
			else
			{
				write(2, "invalid identifier\n", 20);
				error = 1;
			}
			i++;
		}
	}
	if (error)
		ft_exit(1, SET_EXIT_STATUS);
	else
		ft_exit(0, SET_EXIT_STATUS);
}
