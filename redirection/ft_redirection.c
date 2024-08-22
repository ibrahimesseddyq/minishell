/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/22 18:18:37 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int	ft_redirection(t_astnode *ast)
{
	int	fd;
	int stdout_backup = dup(1);  // Backup the current stdout

	while (ast->t_cmd.redirections)
	{
		if (ast->t_cmd.redirections->redir && (ast->t_cmd.redirections->redir->type == NODE_REDIRECT_OUT || ast->t_cmd.redirections->redir->type == NODE_REDIRECT_APPEND))
			fd = ft_red_out(ast);
		else
			fd = ft_red_in(ast);
		ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	}
	return (stdout_backup);
}