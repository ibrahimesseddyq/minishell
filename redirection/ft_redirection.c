/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/15 21:16:44 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_wildcard_data data;

	if (redir->type == NODE_HEREDOC)
		data.pattern = &redir->heredoc;
	else
		data.pattern = &redir->file;
	data.found_count = 0;
	res = expand_wildcard_redir(".", 0, &data);
	// printf("res size [%d]\nres line [%s]\n", res->size, res->expanded_result);
	if (res->size != 1)
	{
		write(2, "ambiguious redir\n", 18);
		ft_exit(1, SET_EXIT_STATUS);
		return (NULL);
	}
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
		ast->t_cmd.redirections->redir->file =handle_ambiguous_wd(ast->t_cmd.redirections->redir);
		if (is_a_redirection_out(ast))
			fd = ft_red_out(ast, env, last_arr[1] == ++i, command_exist);
		else
			fd = ft_red_in(ast, env, last_arr[0] == ++i, command_exist);
		if ((is_a_redirection_out(ast) && last_arr[1] != i)
			|| (!is_a_redirection_out(ast) && last_arr[0] != i))
			ft_close(&fd);
		if (fd == -2)
			return (-2);
		ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	}
	return (fd);
}
