/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:30 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/15 04:29:42 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

char *find_key(char *env)
{
	int i;
	char *tmp;
	tmp = NULL;
	i = 0;
	while(env[i])
	{
		tmp = ft_strjoin(tmp, &env[i]);
		if (env[i + 1] != '=')
			break ;
		i++;
	}
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
