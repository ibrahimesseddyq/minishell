/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/09 18:14:00 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

pid_t exec_and(t_astnode *ast, t_lst *env, int in_fd, int out_fd)
{
    pid_t left_pid = exec_cmd_line(ast->binary.left, env, in_fd, out_fd);
    int status;
    if (left_pid > 0) waitpid(left_pid, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return exec_cmd_line(ast->binary.right, env, in_fd, out_fd);
    }
    return 0;
}
