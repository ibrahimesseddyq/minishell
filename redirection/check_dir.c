/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:13 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 12:55:56 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_no_such_error(t_dir_exist *dir)
{
	struct stat	parent_stat;
	char		*parent_dir;
	char		*last_slash;

	if (!dir->splitted_path[dir->i + 1])
	{
		parent_dir = ft_strdup(dir->full_dir);
		last_slash = ft_strrchr(parent_dir, '/');
		if (last_slash)
			*last_slash = '\0';
		else
			parent_dir = ft_strdup(".");
		if (stat(parent_dir, &parent_stat) == 0
			&& (parent_stat.st_mode & S_IWUSR))
			return (1);
	}
	return (write(2, "no such file or directory\n", 26),
		ft_exit(1, SET_EXIT_STATUS), -2);
}

int	check_dir_has_error(t_dir_exist *dir)
{
	if (!dir->full_dir)
		return (0);
	if (stat(dir->full_dir, &dir->statbuf) != 0)
	{
		return (handle_no_such_error(dir));
	}
	if (dir->splitted_path[dir->i + 1] && !S_ISDIR(dir->statbuf.st_mode))
		return (write(2, "not a directory\n", 15),
			ft_exit(1, SET_EXIT_STATUS), -2);
	if (!dir->splitted_path[dir->i + 1] && S_ISDIR(dir->statbuf.st_mode))
	{
		if (!(dir->statbuf.st_mode & S_IWUSR))
			return (write(2, "permission denied\n", 17),
				ft_exit(1, SET_EXIT_STATUS), -2);
	}
	return (3);
}

void	set_full_dir(t_dir_exist *dir, char *path)
{
	if (path[0] == '/')
	{
		dir->full_dir = ft_strdup("/");
		dir->i = 0;
	}
	else if (path[0] == '.' && path[1] == '/')
	{
		dir->full_dir = ft_strdup("./");
		dir->i = 1;
	}
	else
	{
		dir->full_dir = ft_strdup("./");
		dir->i = 0;
	}
}

void	check_dir_initial(t_dir_exist *dir, int *dir_error, char *path)
{
	if (!path)
		return (0);
	*dir_error = 0;
	dir->splitted_path = ft_split(path, '/');
	if (!dir->splitted_path)
		return (0);
}

int	check_dir_exist(char *path)
{
	t_dir_exist	dir;
	int			dir_error;

	check_dir_initial(&dir, dir_error, path);
	set_full_dir(&dir, path);
	if (!dir.full_dir)
		return (-2);
	while (dir.splitted_path[dir.i])
	{
		if (ft_strlen(dir.splitted_path[dir.i]) == 0)
		{
			dir.i++;
			continue ;
		}
		dir.temp = dir.full_dir;
		dir.full_dir = ft_strjoin(dir.full_dir, dir.splitted_path[dir.i]);
		dir_error = check_dir_has_error(&dir);
		if (dir_error != 3)
			return (dir_error);
		dir.temp = dir.full_dir;
		dir.full_dir = ft_strjoin(dir.full_dir, "/");
		dir.i++;
	}
	return (1);
}
