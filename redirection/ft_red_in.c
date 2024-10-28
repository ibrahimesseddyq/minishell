/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:22:35 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/28 02:21:20 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		gc_free_all();
		exit(1);
	}
	if (is_last && command_exist)
		dup2(fd, 0);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

static int	handle_file_open_and_dup_heredoc(t_redir *heredoc,
		int is_last, int command_exist)
{
	int	fd;

	fd = *heredoc->fd_heredoc_rd;
	if (fd == -2)
		return (-2);
	if (fd < 0)
	{
		ft_close(&fd);
		gc_free_all();
		exit(1);
	}
	if (is_last && command_exist)
		dup2(fd, 0);
	if (!command_exist && fd)
		ft_exit(0, SET_EXIT_STATUS);
	return (fd);
}

int	is_a_redir_in(t_astnode *ast)
{
	if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir
		&& ast->t_cmd.redirections->redir->type == NODE_REDIRECT_IN)
		return (1);
	return (0);
}

void	handle_expanding_and_filename_in(t_astnode *ast, t_lst *env)
{
	int	star_inside;

	star_inside = 0;
	if (star_not_inside_quotes(ast->t_cmd.redirections->redir->file))
		star_inside = 1;
	ast->t_cmd.redirections->redir->file
		= ft_expand_redir(ast->t_cmd.redirections->redir->file, env);
	if (star_inside)
		ast->t_cmd.redirections->redir->file
			= handle_ambiguous_wd(ast->t_cmd.redirections->redir);
	ast->t_cmd.redirections->redir->file
		= make_filename(ast->t_cmd.redirections->redir->file);
}

int	ft_red_in(t_astnode *ast, t_lst *env, int is_last, int command_exist)
{
	int	fd;

	fd = 0;
	if (is_a_redir_in(ast))
	{
		handle_expanding_and_filename_in(ast, env);
		if (ast->t_cmd.redirections->redir->file
			&& !ast->t_cmd.redirections->redir->file[0])
			return (write(2, "No such file or dir\n", 21), -2);
		if (!ast->t_cmd.redirections->redir->file)
			return (write(2, "ambigiuos redir\n", 17), -2);
		ast->t_cmd.redirections->redir->file
			= expand_wd(ast->t_cmd.redirections->redir->file);
		if (handle_ambiguous(ast->t_cmd.redirections->redir->file) == -1)
			return (-2);
		return (handle_file_open_and_dup_in
			(ast->t_cmd.redirections->redir->file, is_last, command_exist));
	}
	else
		return (handle_file_open_and_dup_heredoc
			(ast->t_cmd.redirections->redir, is_last, command_exist));
}
