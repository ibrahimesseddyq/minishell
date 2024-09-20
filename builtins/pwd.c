/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:27:33 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/20 05:24:39 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*ft_pwd(void)
{
	char	*dir;
	char	*path;

	dir = (char *)gcalloc(sizeof(char) * MNSH_PATH_MAX);
	if (!dir)
		return (NULL);
	if (!getcwd(dir, MNSH_PATH_MAX * sizeof(char)))
		return (NULL);
	path = ft_strdup(dir);
	free(dir);
	ft_exit(0, SET_EXIT_STATUS);
	return (path);
}
