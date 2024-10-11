/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/11 16:16:08 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	check_and_open_file(const char *file, int flags, mode_t mode)
// {
// 	struct stat	sb;
// 	int			fd;

// 	stat(file, &sb);
// 	fd = open(file, flags, mode);
// 	if (fd == -1)
// 	{
// 		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
// 			write(2, "Permission denied\n", 19);
// 		else
// 			write(2, "No such file or directory\n", 27);
// 		return (ft_exit(1, SET_EXIT_STATUS), -2);
// 	}
// 	if (!S_ISREG(sb.st_mode))
// 		return (write(2, "Error: Path is not a regular file\n", 35)
// 			, ft_exit(1, SET_EXIT_STATUS), -2);
// 	return (fd);
// }
static int	check_and_open_file(const char *file, int flags, mode_t mode)
{
	struct stat	sb;
	int			fd;

	if (stat(file, &sb) == -1)
	{
		fd = open(file, flags, mode);
		if (fd == -1)
			return (ft_exit(1, SET_EXIT_STATUS), -2);
		return (fd);
	}
	if (!S_ISREG(sb.st_mode))
		return (ft_close(&fd), write(2, "Error: Path is not a regular file\n", 35)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	if (access(file, W_OK) == -1)
		return (ft_close(&fd), write(2, "Permission Denied\n", 19)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	fd = open(file, flags, mode);
	if (fd == -1)
		return (write(2, "Error opening file\n", 20)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	return (fd);
}
static int	handle_file_open_and_dup_out(const char *file,
		int is_last, int command_exist)
{
	int	fd;

	fd = check_and_open_file(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -2)
		return (-2);
	if (is_last && command_exist)
		dup2(fd, 1);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

static int	handle_file_open_and_dup_append(const char *file,
		int is_last, int command_exist)
{
	int	fd;

	fd = check_and_open_file(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -2)
		return (-2);
	if (is_last && command_exist)
		dup2(fd, 1);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

int	ft_red_out(t_astnode *ast, t_lst *env, int is_last, int command_exist)
{
	int		fd;
	t_redir	*redir;

	fd = 0;
	if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir)
	{
		redir = ast->t_cmd.redirections->redir;
		ast->t_cmd.redirections->redir->file
			= ft_expand_redir(ast->t_cmd.redirections->redir->file, env);
		if (!ast->t_cmd.redirections->redir->file)
			return (write(2, "ambigiuos redir\n", 17), -2);
		ast->t_cmd.redirections->redir->file
			= expand_wd(ast->t_cmd.redirections->redir->file);
		if (handle_ambiguous(ast->t_cmd.redirections->redir->file) == -1)
			return (-1);
		if (redir->type == NODE_REDIRECT_OUT)
			return (handle_file_open_and_dup_out
				(ast->t_cmd.redirections->redir->file, is_last, command_exist));
		else if (redir->type == NODE_REDIRECT_APPEND)
			return (handle_file_open_and_dup_append
				(ast->t_cmd.redirections->redir->file, is_last, command_exist));
	}
	return (fd);
}
