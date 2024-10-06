/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:22:35 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/06 16:20:01 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_and_open_file(const char *file, int flags, mode_t mode)
{
	struct stat	sb;
	int			fd;

	if (stat(file, &sb) == -1)
	{
		fd = open(file, flags, mode);
		if (fd == -1)
		{
			if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
				write(2, "Permission denied\n", 19);
			else
				write(2, "No such file or directory\n", 27);
			ft_exit(1, SET_EXIT_STATUS);
			return (-2);
		}
		return (fd);
	}
	if (!S_ISREG(sb.st_mode))
		return (write(2, "Error: Path is not a regular file\n", 35)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	fd = open(file, flags, mode);
	if (fd == -1)
		return (write(2, "Error opening file", 19)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	return (fd);
}

static int	handle_file_open_and_dup_in(const char *file,
		int is_last, int command_exist)
{
	int	fd;

	fd = check_and_open_file(file, O_RDONLY, 0644);
	if (fd == -2)
		return (-2);
	if (fd < 0)
	{
		ft_close(&fd);
		exit(1);
	}
	if (is_last && command_exist)
		dup2(fd, 0);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

static int	handle_file_open_and_dup_heredoc(const char *file,
		int is_last, int command_exist)
{
	int	fd;

	fd = check_and_open_file(file, O_RDONLY | O_CREAT, 0644);
	if (fd == -2)
		return (-2);
	if (fd < 0)
	{
		ft_close(&fd);
		exit(1);
	}
	if (is_last && command_exist)
		dup2(fd, 0);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

int	ft_red_in(t_astnode *ast, t_lst *env, int is_last, int command_exist)
{
	int	fd;

	fd = 0;
	ast->t_cmd.redirections->redir->file
		= ft_expand_redir(ast->t_cmd.redirections->redir->file, env);
	if (!ast->t_cmd.redirections->redir->file)
		return (write(2, "ambigiuos redir\n", 17), -2);
	ast->t_cmd.redirections->redir->file
		= expand_wd(ast->t_cmd.redirections->redir->file);
	if (handle_ambiguous(ast->t_cmd.redirections->redir->file) == -1)
		return (-1);
	if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir
		&& ast->t_cmd.redirections->redir->type == NODE_REDIRECT_IN)
	{
		return (handle_file_open_and_dup_in
			(ast->t_cmd.redirections->redir->file, is_last, command_exist));
	}
	else
	{
		return (handle_file_open_and_dup_heredoc
			(ast->t_cmd.redirections->redir->heredoc, is_last, command_exist));
	}
}
