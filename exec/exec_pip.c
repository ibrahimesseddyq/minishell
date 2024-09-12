/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:51 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/12 13:44:11 by ynachat          ###   ########.fr       */
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
	printf("exit status PIPE %d\n",ft_exit(5, GET_EXIT_STATUS));

		exit(ft_exit(5, GET_EXIT_STATUS));

	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipfd[0], 0);
		close(pipfd[1]);
		exec_cmd_line(ast->binary.right, env);
	printf("exit status PIPE %d\n",ft_exit(5, GET_EXIT_STATUS));

		exit(ft_exit(5, GET_EXIT_STATUS));

	}
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	
}
