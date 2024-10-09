/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:21:53 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/09 22:29:48 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int		stdout_backup;
	int		stdin_backup;
	int		redir_ret;
	char	*pwd_dir;

	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	redir_ret = ft_redirection(ast, env, 1);
	if (redir_ret == -2)
		return (-2);
	if (!ft_strcmp(arg_cmd[0], "echo"))
		ft_echo(arg_cmd);
	else if (!ft_strcmp(arg_cmd[0], "cd"))
		ft_cd(ast->t_cmd.args_size, arg_cmd, SET_EXIT_STATUS, env);
	else if (!ft_strcmp(arg_cmd[0], "pwd"))
	{
		pwd_dir = ft_pwd();
		write(1, pwd_dir, ft_strlen(pwd_dir));
		write(1, "\n", 1);
	}
	else if (!ft_strcmp(arg_cmd[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(arg_cmd[0], "exit"))
		my_exit(arg_cmd, ast->t_cmd.args_size);
	else if (!ft_strcmp(arg_cmd[0], "export"))
		ft_export(arg_cmd, env);
	else if (!ft_strcmp(arg_cmd[0], "unset"))
		unset(arg_cmd, env);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	if (redir_ret != 1)
		ft_close(&redir_ret);
	close(stdout_backup);
	close(stdin_backup);
	return (1);
}

int	check_file(char **argv)
{
	int	is_abs_rel;

	is_abs_rel = 0;
	if (is_relative_absolute(argv[0]))
		is_abs_rel = 1;
	if (access(argv[0], F_OK) == -1)
	{
		if (is_abs_rel)
			write(2, "No such file or directory\n", 27);
		else
			write(2, "command not found\n", 19);
		ft_exit(127, SET_EXIT_STATUS);
		return (0);
	}
	else if (!access(argv[0], F_OK) && (argv[0][0] != '.' && argv[0][0] != '/' ))
	{
		write(2, "command not found\n", 19);
		ft_exit(127, SET_EXIT_STATUS);
		return (0);
	}
	return (1);
}

int	is_builtin_command(const char *cmd)
{
	return (!ft_strcmp((char *)cmd, "echo") || !ft_strcmp((char *)cmd, "cd")
		|| !ft_strcmp((char *)cmd, "pwd") || !ft_strcmp((char *)cmd, "env")
		|| !ft_strcmp((char *)cmd, "exit") || !ft_strcmp((char *)cmd, "export")
		|| !ft_strcmp((char *)cmd, "unset"));
}

int	check_invalid(t_arg_node *arg, char *cmd)
{
	if (!ft_strcmp(arg->arg, "\"\"") || !ft_strcmp(arg->arg, "\'\'")
		|| (!check_valid2(arg->arg) && !ft_strcmp(cmd, "export"))
		|| (!check_valid1(arg->arg) && !ft_strcmp(cmd, "unset")))
	{
		write(2, "invalid identifier\n", 20);
		if (!ft_strcmp(cmd, "export"))
			builtins_state(ACTIVE, EXPORT_BUILTIN, SET_BUILTIN);
		else if (!ft_strcmp(cmd, "unset"))
			builtins_state(ACTIVE, UNSET_BUILTIN, SET_BUILTIN);
	}
	return (1);
}

int	initial_builtin_errors(t_arg_node *args)
{
	char		*cmd;
	t_arg_node	*arg;

	if (!args || !args->arg)
		return (0);
	cmd = args->arg;
	if ((!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")))
	{
		arg = args->next;
		while (arg)
		{
			printf("cmd is [%s] and arg is [%s]\n", cmd, arg->arg);
			check_invalid(arg, cmd);
			arg = arg->next;
		}
	}
	return (0);
}
