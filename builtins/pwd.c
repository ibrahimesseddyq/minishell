/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:27:33 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/26 23:54:51 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*ft_pwd(t_lst *env)
{
	char	*dir;
	char	*path;
	char	*oldpwd;

	dir = (char *)gcalloc(sizeof(char) * MNSH_PATH_MAX);
	if (!ft_getcwd(dir, MNSH_PATH_MAX * sizeof(char)))
	{
		oldpwd = get_env(env, "OLDPWD");
		if (!oldpwd)
			path = ft_strdup(SECURE_PATH);
		else
			path = get_env(env, "OLDPWD");
		ft_exit(1, SET_EXIT_STATUS);
		return (path);
	}
	else
		path = ft_strdup(dir);
	ft_exit(0, SET_EXIT_STATUS);
	return (path);
}
