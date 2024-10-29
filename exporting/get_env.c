/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:18:32 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 08:55:24 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_lst *env, char *the_env)
{
	if (!the_env || !the_env[0])
		return (NULL);
	while (env)
	{
		if (!env->key)
			return (NULL);
		if (ft_strcmp(env->key, the_env) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_env_isset(t_lst *env, char *the_env)
{
	if (!the_env || !the_env[0])
		return (0);
	while (env)
	{
		if (!env->key)
			return (0);
		if (ft_strcmp(env->key, the_env) == 0)
			return (env->set);
		env = env->next;
	}
	return (0);
}
