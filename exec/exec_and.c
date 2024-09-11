/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/10 21:11:49 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

pid_t exec_and(t_astnode *ast, t_lst *env)
{
    pid_t left_pid = exec_cmd_line(ast->binary.left, env);
    int status;
    if (left_pid > 0) waitpid(left_pid, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return exec_cmd_line(ast->binary.right, env);
    }
    return 0;
}
