/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:51 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/08 10:37:43 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_pip(t_astnode *ast, t_lst *env)
{

	int		pipfd[2];
	int		pid;
	int		pid2;

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipfd[1], 1);
		close(pipfd[0]);
		exec_cmd_line(ast->binary.left, env);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipfd[0], 0);
		close(pipfd[1]);
		exec_cmd_line(ast->binary.right, env);
		exit(0);
	}
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
}
