/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:03:49 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 09:21:31 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	permission_denied_error(void)
{
	write(2, "permission denied\n", 19);
	ft_exit(126, SET_EXIT_STATUS);
}

void	no_such_file_or_dir_error(void)
{
	write(2, "no such file or directory\n", 27);
	ft_exit(127, SET_EXIT_STATUS);
}

char	*check_file_no_path(char *cmd)
{
	if (!is_directory(cmd))
		return (is_directory_error(), NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (access(cmd, F_OK) == 0)
	{
		if (is_directory(cmd) == 2 && access(cmd, X_OK))
			return (permission_denied_error(), NULL);
	}
	if (access(cmd, F_OK) != 0)
	{
		return (no_such_file_or_dir_error(), NULL);
	}
	return (cmd);
}

char	*handle_slash_path(char *cmd)
{
	if (!is_directory(cmd))
		return (is_directory_error(), NULL);
	else if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	else if (access(cmd, F_OK) != 0)
		return (no_such_file_or_dir_error(), NULL);
	else
		return (permission_denied_error(), NULL);
}

char	*check_file_with_path(char *cmd, t_lst *env)
{
	char	*cmd_final;
	char	**paths;

	paths = ft_split(get_env(env, "PATH"), ':');
	if (!paths)
	{
		no_such_file_or_dir_error();
		gc_free_all();
		exit(1);
	}
	if (ft_strchr(cmd, '/'))
	{
		return (handle_slash_path(cmd));
	}
	cmd_final = find_command_in_path(cmd, paths);
	if (cmd_final)
		return (cmd_final);
	if (!cmd_final && !ft_strchr(cmd, '/'))
		return (write(2, "command not found \n", 20),
			ft_exit(127, SET_EXIT_STATUS), NULL);
	return (cmd_final);
}
