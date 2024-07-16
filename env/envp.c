/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:30 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/16 15:13:11 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void	free_mat(char **mtr)
{
	int	i;

	i = 0;
	while (mtr[i])
	{
		free(mtr[i]);
		i++;
	}
	free(mtr);
}

char *find_key(char *env)
{
	int i;
	int j;
	char *tmp;
	tmp = NULL;
	i = 0;
	j = 0;
	while (env[j] && env[j] != '=')
		j++;
	tmp = ft_strdup(ft_substr(env, 0, j));

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
