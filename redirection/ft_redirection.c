/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/06 04:11:35 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void ft_redirection(t_astnode *ast)
{


	// while (ast->t_cmd.redirections)
	// {
	// 	printf("----------> %s\n", ast->t_cmd.redirections->redir->file);
	// 	ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	// }
	while (ast->t_cmd.redirections)
	{
		if (ast->t_cmd.redirections->redir && (ast->t_cmd.redirections->redir->type == NODE_REDIRECT_OUT || ast->t_cmd.redirections->redir->type == NODE_REDIRECT_APPEND))
			ft_red_out(ast);
		else
			ft_red_in(ast);
		ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	}
}