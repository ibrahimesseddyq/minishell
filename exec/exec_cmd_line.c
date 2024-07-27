/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:09 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/27 21:50:08 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_cmd_line(t_astnode *ast, t_st *st)
{
	if (ast->type == NODE_COMMAND)
		exec_cmd(ast, st);
	else if (ast->type == NODE_PIPE)
		exec_pip(ast);
	else if (ast->type == NODE_LOGICAL_AND)
		exec_and(ast, st);
	else if (ast->type == NODE_LOGICAL_OR)
		exec_or(ast, st);
	else if (ast->type == NODE_BLOCK)
		exec_cmd_line(ast->block.child, st);
}
