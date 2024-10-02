/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/02 09:08:06 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_env_and_exec(char **arg_cmd, t_lst *env, int fd)
{
	char	**envp;

	envp = build_envp(env);
	if (!envp)
		exit(1);
	if (!check_file(arg_cmd))
	{
		ft_close(&fd);
		exit(127);
	}
	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
	{
		handle_exec_error();
		exit(1);
	}
}

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
	if (!check_file(arg_cmd))
		(ft_close(&fd), exit(127));

	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
		(handle_exec_error(), exit(1));
	return (1);
}

int	execute_external(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int		pid;
	int		child_status;
	struct termios	state;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDOUT_FILENO, &state);
	pid = ft_fork();
	if (pid == 0)
	{
		if (execute_child(arg_cmd, ast, env) == -2)
			exit(1);
		// clean_fd();
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &child_status, 0);
		if (WIFEXITED(child_status))
			ft_exit (WEXITSTATUS(child_status), SET_EXIT_STATUS);
		else if (WIFSIGNALED(child_status))
			ft_exit(128 + WTERMSIG(child_status), SET_EXIT_STATUS);
	}
	else
		ft_exit(1, SET_EXIT_STATUS);
	if (WIFSIGNALED(child_status) && WTERMSIG(child_status) == SIGQUIT)
		tcsetattr(STDOUT_FILENO, TCSANOW, &state);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	return (1);
}

char	*find_command_in_path(const char *cmd, char **path_dirs)
{
	char	*cmd_with_slash;
	int		i;
	char	*full_path;

	i = 0;
	cmd_with_slash = ft_strjoin("/", (char *)cmd);
	if (!cmd_with_slash)
		return (NULL);
	while (path_dirs[i])
	{
		full_path = ft_strjoin(path_dirs[i], cmd_with_slash);
		if (!full_path)
			continue ;
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

t_arg_node	*get_node_at(t_arg_node *lst, int pos)
{
	int			i;
	t_arg_node	*head;

	i = 0;
	head = lst;
	while (head)
	{
		if (i == pos)
			return (head);
		i++;
		head = head->next;
	}
	return (NULL);
}
