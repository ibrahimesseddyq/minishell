/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:51 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/26 02:38:45 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_processes(int pid1, int pid2)
{
	int	cmd_status;
	int	cmd_status2;

	waitpid(pid2, &cmd_status, 0);
	waitpid(pid1, &cmd_status2, 0);
	if (WIFEXITED(cmd_status))
	{
		ft_exit(WEXITSTATUS(cmd_status), SET_EXIT_STATUS);
	}
	else if (WIFSIGNALED(cmd_status))
		ft_exit(128 + WTERMSIG(cmd_status), SET_EXIT_STATUS);
}

void	handle_child_process(t_astnode *cmd,
		t_lst *env, int read_fd, int write_fd)
{
	if (write_fd != -1)
	{
		dup2(write_fd, 1);
		ft_close(&write_fd);
	}
	if (read_fd != -1)
	{
		dup2(read_fd, 0);
		ft_close(&read_fd);
	}
	exec_cmd_line(cmd, env);
	exit(ft_exit(5, GET_EXIT_STATUS));
}

void	exec_pip(t_astnode *ast, t_lst *env)
{
	int		pipfd[2];
	int		pid;
	int		pid2;

	pipe(pipfd);
	pid = ft_fork();
	if (pid == 0)
	{
		ft_close(&pipfd[0]);
		handle_child_process(ast->t_binary.left, env, -1, pipfd[1]);
	}
	pid2 = ft_fork();
	if (pid2 == 0)
	{
		ft_close(&pipfd[1]);
		handle_child_process(ast->t_binary.right, env, pipfd[0], -1);
	}
	ft_close(&pipfd[1]);
	ft_close(&pipfd[0]);
	wait_for_processes(pid, pid2);
}
