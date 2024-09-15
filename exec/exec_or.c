/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:39 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/14 20:43:45 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

pid_t	exec_or(t_astnode *ast, t_lst *env)
{
	pid_t	left_pid;
	int		status;

	left_pid = exec_cmd_line(ast->binary.left, env);
	if (left_pid > 0)
		waitpid(left_pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (exec_cmd_line(ast->binary.right, env));
	return (0);
}
