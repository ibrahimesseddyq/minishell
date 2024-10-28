/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/28 02:21:15 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_and_open_file_out(const char *file, int flags, mode_t mode)
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
		return (ft_close(&fd),
			write(2, "Error: Path is not a regular file\n", 35)
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

	fd = check_and_open_file_out(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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

	fd = check_and_open_file_out(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -2)
		return (-2);
	if (is_last && command_exist)
		dup2(fd, 1);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

void	handle_expanding_and_filename_out(t_astnode *ast,
			t_lst *env, t_redir *redir)
{
	int	star_inside;

	star_inside = 0;
	if (star_not_inside_quotes(redir->file))
		star_inside = 1;
	redir->file = ft_expand_redir(redir->file, env);
	if (redir->file && star_inside)
		redir->file = handle_ambiguous_wd(redir);
	if (redir->file)
		redir->file = make_filename(redir->file);
}

int	ft_red_out(t_astnode *ast, t_lst *env, int is_last, int command_exist)
{
	int		fd;
	t_redir	*redir;

	fd = 0;
	if (!ast->t_cmd.redirections || !ast->t_cmd.redirections->redir)
		return (fd);
	redir = ast->t_cmd.redirections->redir;
	handle_expanding_and_filename_out(ast, env, redir);
	if (check_error_redir_out(redir) == -2)
		return (-2);
	redir->file = expand_wd(redir->file);
	if (handle_ambiguous(redir->file) == -1)
		return (-2);
	if (redir->type == NODE_REDIRECT_OUT)
		return (handle_file_open_and_dup_out
			(redir->file, is_last, command_exist));
	else if (redir->type == NODE_REDIRECT_APPEND)
		return (handle_file_open_and_dup_append(redir->file, is_last, \
		command_exist));
	return (fd);
}
