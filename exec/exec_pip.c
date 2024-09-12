/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:51 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/12 18:40:02 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>
#include <glob.h>

void exec_pip(t_astnode *ast, t_lst *env)
{

	int		pipfd[2];
	int		pid;
	int		pid2;
    int cmd_status;
    int cmd_status2;



	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipfd[1], 1);
		close(pipfd[0]);
		exec_cmd_line(ast->binary.left, env);
	// printf("exit status PIPE %d\n",ft_exit(5, GET_EXIT_STATUS));

		exit(ft_exit(5, GET_EXIT_STATUS));

	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipfd[0], 0);
		close(pipfd[1]);
		exec_cmd_line(ast->binary.right, env);
	// printf("exit status PIPE %d\n",ft_exit(5, GET_EXIT_STATUS));

		exit(ft_exit(5, GET_EXIT_STATUS));

	}
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid2, &cmd_status, 0);
	waitpid(pid, &cmd_status2, 0);
	if (WIFEXITED(cmd_status))
            ft_exit (WEXITSTATUS(cmd_status), SET_EXIT_STATUS);
    else if (WIFSIGNALED(cmd_status))
            ft_exit(128 + WTERMSIG(cmd_status), SET_EXIT_STATUS);
	// ft_exit(*status, SET_EXIT_STATUS);
	printf("[2 exit status PIPE %d %d]\n",WEXITSTATUS(cmd_status), WEXITSTATUS(cmd_status2));

}
