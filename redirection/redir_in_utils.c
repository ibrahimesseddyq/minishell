/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:30:25 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 08:35:39 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambiguious_wildcard(char *str)
{
	char	*del;
	int		i;

	i = 0;
	del = get_splitted_char(1);
	while (str[i])
	{
		if (str[i] == *del)
			return (1);
		i++;
	}
	return (0);
}

int	handle_ambiguous(char *str)
{
	if (check_ambiguious_wildcard(str))
	{
		write(2, "ambiguous redir\n", 17);
		ft_exit(1, SET_EXIT_STATUS);
		return (-1);
	}
	return (1);
}
int	check_dir_exist(char *path)
{
	char		**splitted_path;
	int			i;
	struct stat	statbuf;
	char		*full_dir;

	full_dir = NULL;
	splitted_path = ft_split(path, '/');
	if (splitted_path && splitted_path[0])
		full_dir = splitted_path[0];
	else
		full_dir = ft_strdup("");
	i  = 1;
	while(splitted_path[i])
	{
		if (splitted_path[i] && splitted_path[i + 1])
		{
			full_dir = ft_strjoin(ft_strjoin(full_dir, "/"), splitted_path[i]);
			if (stat(full_dir, &statbuf) != 0)
			{
				write(2, "no such file or directory\n", 27);
				ft_exit(127, SET_EXIT_STATUS);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
int	check_error_redir_out(t_redir *redir)
{
	if (redir->file && !redir->file[0])
		return (write(2, "No such file or dir\n", 21), -2);
	if (!redir->file)
		return (write(2, "ambigiuos redir\n", 17), -2);
	if (!check_dir_exist(redir->file))
		return (-2);
	return (1);
}
