/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:30 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/31 03:56:18 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"



char *find_key(char *env)
{
	int i;
	i = 0;
	char *tmp;
	tmp = NULL;
	while (env[i] && env[i] != '=')
		i++;
	tmp = ft_strdup(ft_substr(env, 0, i));
	return (tmp);
}
t_lst	*envp(char **env)
{
	t_lst *lst;
	t_lst *new;
	int i;

	i = 0;
	lst = NULL;
	lst = ft_lstadd_new_env(find_key(env[i]),ft_strchr(env[i], '=') + 1);
	i++;
	while (env[i])
	{
		new = ft_lstadd_new_env(find_key(env[i]),ft_strchr(env[i], '=') + 1);
		ft_lstadd_back_env(&lst, new);
		i++;
	}
	return (lst);
	
}