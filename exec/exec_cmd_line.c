/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:09 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/09 18:13:49 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "../frontend/frontend.h"

pid_t exec_cmd_line(t_astnode *ast, t_lst *env, int in_fd, int out_fd)
{
    pid_t pid = 0;

    if (ast->type == NODE_COMMAND)
        pid = exec_cmd(ast, env, in_fd, out_fd);
    else if (ast->type == NODE_PIPE) {
        exec_pip(ast, env);
        // For pipes, we don't return a PID as exec_pip handles its own processes
    }
    else if (ast->type == NODE_LOGICAL_AND)
        pid = exec_and(ast, env, in_fd, out_fd);
    else if (ast->type == NODE_LOGICAL_OR)
        pid = exec_or(ast, env, in_fd, out_fd);
    else if (ast->type == NODE_BLOCK)
        pid = exec_cmd_line(ast->block.child, env, in_fd, out_fd);

    return pid;
}