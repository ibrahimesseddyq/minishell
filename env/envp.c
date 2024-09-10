/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:30 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/10 15:27:10 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

char *find_key(char *env)
{
    int i = 0;
    while (env[i] && env[i] != '=')
        i++;
    return ft_substr(env, 0, i);
}

char *find_value(char *env)
{
    char *equal_sign = ft_strchr(env, '=');
    if (equal_sign)
        return ft_strdup(equal_sign + 1);
    return ft_strdup("");
}
t_lst *envp(char **env)
{
    t_lst *lst = NULL;
    t_lst *new;
	char signe;
    int i = 0;

    while (env[i])
    {
        char *key = find_key(env[i]);
        char *value = find_value(env[i]);
		if(ft_strchr(env[i], '='))
			signe = '=';
		else
			signe = '\0';
        new = ft_lstadd_new_env(key, value, signe);
        new->set = 1;
        if (!new)
            return NULL;
        ft_lstadd_back_env(&lst, new);
        i++;
    }

    return lst;
}