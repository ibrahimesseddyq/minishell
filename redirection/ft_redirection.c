/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/27 23:55:55 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_redirection_out(t_astnode *ast)
{
	if ((ast->t_cmd.redirections->redir->type == NODE_REDIRECT_OUT
			|| ast->t_cmd.redirections->redir->type == NODE_REDIRECT_APPEND)
		&& ast->t_cmd.redirections->redir)
		return (1);
	return (0);
}

char	*handle_ambiguous_wd(t_redir *redir)
{
	t_wd_redir_res	*res;
	t_wildcard_data	data;
	char			*pattern;

	if (check_if_directory(redir->file))
		return (NULL);
	if (redir->type == NODE_HEREDOC)
		pattern = redir->heredoc;
	else
		pattern = redir->file;
	data.found_count = 0;
	res = expand_wd_redir(pattern);
	if (res->size != 1 && res->size != 0)
	{
		ft_exit(1, SET_EXIT_STATUS);
		return (NULL);
	}
	if (!res->expanded_result)
		return (redir->file);
	else
		return (res->expanded_result);
}

int	ft_redirection(t_astnode *ast, t_lst *env, int command_exist)
{
	int	fd;
	int	last_arr[2];
	int	i;

	(1) && (last_arr[0] = get_last_redirs(ast)[0],
		last_arr[1] = get_last_redirs(ast)[1], i = -1, fd = -1);
	if (last_arr[0] == 0 && last_arr[1] == 0)
		return (1);
	while (ast->t_cmd.redirections)
	{
		if (!ast->t_cmd.redirections->redir->file)
			return (-2);
		if (is_a_redirection_out(ast))
			fd = ft_red_out(ast, env, last_arr[1] == ++i, command_exist);
		else
			fd = ft_red_in(ast, env, last_arr[0] == ++i, command_exist);
		if ((is_a_redirection_out(ast) && last_arr[1] != i)
			|| (!is_a_redirection_out(ast) && last_arr[0] != i)
			|| (!is_a_redirection_out(ast) && !is_a_redir_in(ast)))
			ft_close(&fd);
		if (fd == -2)
			return (-2);
		ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	}
	return (fd);
}

void	close_heredoc_fds(t_astnode *ast)
{
	t_redir_list	*redirections;

	redirections = ast->t_cmd.redirections;
	while (redirections)
	{
		if (redirections->redir && redirections->redir->fd_heredoc_rd)
		{
			ft_close(redirections->redir->fd_heredoc_rd);
		}
		redirections = redirections->next;
	}
}

void	close_command_heredocs(t_astnode *cmd)
{
	t_redir_list	*redirections;

	if (!cmd || !cmd->t_cmd.redirections)
		return ;
	redirections = cmd->t_cmd.redirections;
	while (redirections)
	{
		if (redirections->redir
			&& redirections->redir->type == NODE_HEREDOC
			&& redirections->redir->fd_heredoc_rd)
		{
			ft_close(redirections->redir->fd_heredoc_rd);
		}
		redirections = redirections->next;
	}
}
