/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:21:53 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 05:51:26 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_builtin_command(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	char	*pwd_dir;

	if (!ft_strcmp(arg_cmd[0], "echo"))
		ft_echo(arg_cmd);
	else if (!ft_strcmp(arg_cmd[0], "cd"))
		ft_cd(ast->t_cmd.args_size, arg_cmd, env);
	else if (!ft_strcmp(arg_cmd[0], "pwd"))
		(1) && (pwd_dir = ft_pwd(env),
			write(1, pwd_dir, ft_strlen(pwd_dir)), write(1, "\n", 1));
	else if (!ft_strcmp(arg_cmd[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(arg_cmd[0], "exit"))
		my_exit(arg_cmd, ast->t_cmd.args_size);
	else if (!ft_strcmp(arg_cmd[0], "export"))
		ft_export(arg_cmd, env);
	else if (!ft_strcmp(arg_cmd[0], "unset"))
		unset(arg_cmd, env);
}

int	execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int		stdout_backup;
	int		stdin_backup;
	int		redir_ret;

	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	redir_ret = ft_redirection(ast, env, 1);
	if (redir_ret == -2)
		return (ft_close(&stdin_backup), ft_close(&stdout_backup), -2);
	execute_builtin_command(arg_cmd, ast, env);
	if (redir_ret != 1)
		ft_close(&redir_ret);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	ft_close(&stdout_backup);
	ft_close(&stdin_backup);
	return (1);
}

char	*check_file(char **argv, t_lst *env)
{
	char	*path;

	path = get_env(env, "PATH");
	if (!path)
		return (check_file_no_path(argv[0]));
	else
		return (check_file_with_path(argv[0], env));
	return (argv[0]);
}

void	is_directory_error(void)
{
	write(2, "is a directory\n", 16);
	ft_exit(126, SET_EXIT_STATUS);
}
