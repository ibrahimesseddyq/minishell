/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/13 14:29:43 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int	ft_redirection(t_astnode *ast, t_lst *env, int command_exist)
{
	int	fd;
	int is_last;
	int stdout_backup = dup(1);

	is_last = 0;
    printf("[ft_redirection] rntered her\n");

	while (ast->t_cmd.redirections)
	{
		    printf("[ft_redirection] rntered her 2\n");

		if(ast->t_cmd.redirections->next == NULL)
			is_last = 1;
		if (ast->t_cmd.redirections->redir && (ast->t_cmd.redirections->redir->type == NODE_REDIRECT_OUT || ast->t_cmd.redirections->redir->type == NODE_REDIRECT_APPEND))
		{
			fd = ft_red_out(ast, env, is_last, command_exist);
			if (fd == -2)
				return (-2);
		}
		else
		{
			fd = ft_red_in(ast, env, is_last, command_exist);
			if (fd == -2)
				return (-2);
		}
		ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	}
	// printf("end redir\n");
	return (stdout_backup);
}