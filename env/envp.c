/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:30 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/22 01:50:57 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_key(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

char	*find_value(char *env)
{
	char	*equal_sign;

	equal_sign = NULL;
	equal_sign = ft_strchr(env, '=');
	if (equal_sign)
		return (ft_strdup(equal_sign + 1));
	return (ft_strdup(""));
}

void	add_to_env(char *key, char *value, char signe, t_lst **lst)
{
	t_lst	*new;

	new = NULL;
	new = ft_lstadd_new_env(key, value, signe);
	ft_lstadd_back_env(lst, new);
}

t_lst	*envp(char **env)
{
	t_lst	*lst;
	char	signe;
	int		i;
	char	*key;
	char	*value;

	lst = NULL;
	i = 0;
	while (env[i])
	{
		key = find_key(env[i]);
		value = find_value(env[i]);
		if (ft_strchr(env[i], '='))
			signe = '=';
		else
			signe = '\0';
		add_to_env(key, value, signe, &lst);
		i++;
	}
	return (lst);
}
