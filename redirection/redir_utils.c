/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:48:07 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 11:44:02 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_just(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

char	*make_filename(char *file)
{
	file = skip_char(file, *get_splitted_char(5));
	if (!file[0])
		return (NULL);
	if (contains_just(file, *get_splitted_char(3)) || !file[0])
	{
		return (ft_strdup(""));
	}
	file = skip_char(file, *get_splitted_char(3));
	return (file);
}

int	check_and_open_file(const char *file, int flags, mode_t mode)
{
	struct stat	sb;
	int			fd;

	stat(file, &sb);
	fd = open(file, flags, mode);
	if (fd == -1)
	{
		if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
			write(2, "Permission denied\n", 19);
		else
			write(2, "No such file or directory\n", 27);
		return (ft_exit(1, SET_EXIT_STATUS), -2);
	}
	if (!S_ISREG(sb.st_mode))
		return (ft_close(&fd),
			write(2, "Error: Path is not a regular file\n", 35)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	if (access(file, R_OK) == -1)
		return (ft_close(&fd), write(2, "Permission Denied\n", 19)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	return (fd);
}

int	check_if_directory(char *cmd)
{
	struct stat	sb;

	stat(cmd, &sb);
	if ((cmd[ft_strlen(cmd) - 1] == '/' && S_ISDIR(sb.st_mode))
		|| (S_ISDIR(sb.st_mode)
			&& !is_builtin_command(cmd) && slash_exist(cmd)))
	{
		write(2, "Is a directory \n", 17);
		ft_exit(126, SET_EXIT_STATUS);
		return (1);
	}
	return (0);
}

int	*get_last_redirs(t_astnode *ast)
{
	int				last_in;
	int				last_out;
	int				i;
	int				*last_arr;
	t_redir_list	*current;

	current = ast->t_cmd.redirections;
	last_arr = gcalloc(sizeof(int) * 2);
	i = 0;
	last_out = -1;
	last_in = -1;
	while (current)
	{
		if (current->redir && (current->redir->type == NODE_REDIRECT_OUT
				|| current->redir->type == NODE_REDIRECT_APPEND))
			last_out = i;
		else
			last_in = i;
		i++;
		current = current->next;
	}
	last_arr[0] = last_in;
	last_arr[1] = last_out;
	return (last_arr);
}
