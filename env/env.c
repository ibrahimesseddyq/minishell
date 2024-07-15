/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:30 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/15 01:54:02 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"


int find_key(char *env)
{
	int i;
	char *tmp;
	i = 0;
	while(env[i] && env[i] != '=')
	{
		tmp = ft_strjoin(tmp,env[i]);
		i++;
	}
	return (0);
}

void	env(char **env)
{
	t_lst *lst;
	t_lst *new;
	int i;

	i = 0;
	while (lst)
	{
		new = ft_lstadd_new_env(find_key(env[i]),find_value(env[i]));
		i++;
		lst = lst->next;
	}
}