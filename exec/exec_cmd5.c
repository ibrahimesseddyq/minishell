/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 09:17:25 by ibes-sed         ###   ########.fr       */
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
	{
		gc_free_all();
		exit(1);
	}
	if (!check_file(arg_cmd, env))
		return (ft_close(&fd), 0);
	arg_cmd[0] = check_file(arg_cmd, env);
	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
	{
		handle_exec_error();
		gc_free_all();
		exit(1);
	}
	return (1);
}

static void	handle_child_process(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	execute_child(arg_cmd, ast, env);
}

static void	handle_parent_process(int pid, int *child_status, t_astnode *ast)
{
	t_redir_list	*tmp;

	tmp = ast->t_cmd.redirections;
	waitpid(pid, child_status, 0);
	if (WIFEXITED(*child_status))
		ft_exit(WEXITSTATUS(*child_status), SET_EXIT_STATUS);
	else if (WIFSIGNALED(*child_status))
		ft_exit(128 + WTERMSIG(*child_status), SET_EXIT_STATUS);
	while (tmp)
	{
		if (tmp->redir && tmp->redir->fd_heredoc_rd)
			ft_close(tmp->redir->fd_heredoc_rd);
		tmp = tmp->next;
	}
}

void	restore_signal_handlers(void)
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
	tcgetattr(STDIN_FILENO, &state);
	pid = ft_fork();
	if (pid == 0)
		handle_child_process(arg_cmd, ast, env);
	else if (pid > 0)
		handle_parent_process(pid, &child_status, ast);
	else
		ft_exit(1, SET_EXIT_STATUS);
	if (WIFSIGNALED(child_status) && WTERMSIG(child_status) == SIGQUIT)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &state);
		tcsetattr(STDIN_FILENO, TCSANOW, &state);
		printf("Quit: 3\n");
	}
	restore_signal_handlers();
	return (1);
}
