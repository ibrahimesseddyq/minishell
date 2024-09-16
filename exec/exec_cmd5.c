/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/16 18:47:06 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void	setup_env_and_exec(char **arg_cmd, t_lst *env, int fd)
{
	char	**envp;

	envp = build_envp(env);
	if (!envp)
		exit(1);
	if (!check_file(arg_cmd))
	{
		close(fd);
		exit(127);
	}
	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
	{
		handle_exec_error(arg_cmd[0]);
		exit(1);
	}
}

int	execute_child(char **arg_cmd, t_astnode *ast, t_lst *env, int *fd)
{
	char	**envp;

	*fd = ft_redirection(ast, env, 1);
	if (*fd == -2)
		return (-2);

	envp = build_envp(env);
	if (!envp)
		exit(1);
	if (!check_file(arg_cmd))
		(close(*fd), exit(127));
	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
		(handle_exec_error(arg_cmd[0]), exit(1));
	exit(0);
}

int	execute_external(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int		pid;
	int		fd;
	int		stdout_backup;
	int		child_status;

	pid = fork();
	stdout_backup = dup(1);
	if (pid == 0)
		if (execute_child(arg_cmd, ast, env, fd) == -2)
		{
			exit(1);
		}
	else if (pid > 0)
	{
		waitpid(pid, &child_status, 0);
		(dup2(stdout_backup, 1), close(stdout_backup));
		if (fd != stdout_backup)
			close(fd);
		if (WIFEXITED(child_status))
			ft_exit (WEXITSTATUS(child_status), SET_EXIT_STATUS);
		else if (WIFSIGNALED(child_status))
			ft_exit(128 + WTERMSIG(child_status), SET_EXIT_STATUS);
	}
	else
		ft_exit(1, SET_EXIT_STATUS);

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
