/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:09 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/18 06:54:39 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_cmd_line(t_astnode *ast, t_lst *env)
{
	if (ast->type == NODE_COMMAND)
		exec_cmd(ast, env);
	else if (ast->type == NODE_PIPE)
		exec_pip(ast, env);
	else if (ast->type == NODE_LOGICAL_AND)
		exec_and(ast, env);
	else if (ast->type == NODE_LOGICAL_OR)
		exec_or(ast, env);
	else if (ast->type == NODE_BLOCK)
		exec_cmd_line(ast->block.child, env);
}
