/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:09 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/28 05:47:47 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd_line(t_astnode *ast, t_lst *env)
{
	if (ast->type == NODE_COMMAND)
		exec_cmd(ast, env);
	else if (ast->type == NODE_PIPE)
	{
		signal(SIGINT, handle_sigint);
		exec_pip(ast, env);
		restore_signal_handlers();
	}
	else if (ast->type == NODE_LOGICAL_AND)
		exec_and(ast, env);
	else if (ast->type == NODE_LOGICAL_OR)
		exec_or(ast, env);
	else if (ast->type == NODE_BLOCK)
		exec_cmd_line(ast->t_block.child, env);
}
