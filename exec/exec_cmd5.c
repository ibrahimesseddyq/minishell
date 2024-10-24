/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/24 02:25:50 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_child(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	char	**envp;
	int		fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	fd = ft_redirection(ast, env, 1);
	if (fd == -2)
		return (-2);
	envp = build_envp(env);
	if (!envp)
		exit(1);
	if (!check_file(arg_cmd, env))
		(ft_close(&fd), exit(127));
	printf("cmfffffd [%s]\n", arg_cmd[0]);
	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
	{
		handle_exec_error(); 
		exit(1);
	}
	return (1);
}

static void	handle_child_process(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	if (execute_child(arg_cmd, ast, env) == -2)
		exit(1);
	exit(0);
}

static void	handle_parent_process(int pid, int *child_status)
{
	waitpid(pid, child_status, 0);
	if (WIFEXITED(*child_status))
		ft_exit(WEXITSTATUS(*child_status), SET_EXIT_STATUS);
	else if (WIFSIGNALED(*child_status))
		ft_exit(128 + WTERMSIG(*child_status), SET_EXIT_STATUS);
}

static void	restore_signal_handlers(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}

int	execute_external(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int				pid;
	int				child_status;
	struct termios	state;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDOUT_FILENO, &state);
	pid = ft_fork();
	if (pid == 0)
		handle_child_process(arg_cmd, ast, env);
	else if (pid > 0)
		handle_parent_process(pid, &child_status);
	else
		ft_exit(1, SET_EXIT_STATUS);
	if (WIFSIGNALED(child_status) && WTERMSIG(child_status) == SIGQUIT)
		tcsetattr(STDOUT_FILENO, TCSANOW, &state);
	restore_signal_handlers();
	return (1);
}
