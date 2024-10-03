/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/03 11:27:19 by ibes-sed         ###   ########.fr       */
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
	t_lst *tmp;
	tmp = lst;

	tmp = lst;

	if (!str[1] && !builtins_state(-1, EXPORT_BUILTIN, GET_BUILTIN))
		print_export(lst);
	else
	{
		printf("\n\nstr is [%s]\n\n", str[i]);
		while (str[i])
		{
			printf("str export is [%s]\n", str[i]);
			if (check_valid2(str[i]) && str[i][0])
			{
				printf("entered export\n");
				export_var(str, lst, i);
			}
			i++;
		}
	}

	if (builtins_state(-1, EXPORT_BUILTIN, GET_BUILTIN))
		ft_exit(1, SET_EXIT_STATUS);
	else
		ft_exit(0, SET_EXIT_STATUS);
	builtins_state(INACTIVE, EXPORT_BUILTIN, SET_BUILTIN);
}
