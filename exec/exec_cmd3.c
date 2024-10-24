/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:19:45 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 23:04:36 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_if_in_paths(char *cmd, t_lst *env)
{
	char	*path;
	char	**path_dirs;
	char	*cmd_path;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.' || is_builtin_command(cmd))
		return (ft_strdup(cmd));
	path = get_env(env, "PATH");
	if (!path)
		return (ft_strdup(cmd));
	path_dirs = ft_split(path, ':');
	if (!path_dirs)
		return (ft_strdup(cmd));
	cmd_path = find_command_in_path(cmd, path_dirs);
	if (cmd_path)
		return (cmd_path);
	else
		return (ft_strdup(cmd));
}

int	is_absolute_path(const char *path)
{
	return (path[0] == '/');
}

int	is_relative_path(const char *path)
{
	return (path[0] == '.' && (path[1] == '/'
			|| (path[1] == '.' && path[2] == '/')));
}

int	is_relative_absolute(const char *path)
{
	if (is_absolute_path(path))
		return (1);
	else if (is_relative_path(path))
		return (1);
	else
		return (0);
}
