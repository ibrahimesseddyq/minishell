/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 23:30:34 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/12 01:13:27 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_tilde(char *path, t_lst *env)
{
	char	*home;

	if (path[0] == '~')
	{
		home = get_env(env, "HOME");
		if (!home)
			return (ft_strdup(path));
		return (ft_strjoin(home, path + 1));
	}
	return (ft_strdup(path));
}
