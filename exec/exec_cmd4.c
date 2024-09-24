/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:21:53 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/24 00:34:40 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int		stdout_backup;
	char	*pwd_dir;

	stdout_backup = ft_redirection(ast, env, 1);
	printf("command is [%s]\n", arg_cmd[0]);
	if (stdout_backup == -2)
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
		printf("here3\n");
		if (is_abs_rel)
			write(2, "No such file or directory\n", 27);
		else
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
int	check_valid2(char *str)
{
	if (str[0] == '?' || str[0] == '=' || str[0] == '-')
		return (0);
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
		printf("command [%s]\n", cmd);
		arg = args->next;
		while (arg)
		{
			if (!ft_strcmp(arg->arg, "\"\"") || !ft_strcmp(arg->arg, "\'\'") || !check_valid2(arg->arg))
			{
				write(2, "invalid identifier\n", 20);
				if (!ft_strcmp(cmd, "export"))
					builtins_state(ACTIVE, EXPORT_BUILTIN, SET_BUILTIN);
				else if (!ft_strcmp(cmd, "unset"))
					builtins_state(ACTIVE, UNSET_BUILTIN, SET_BUILTIN);
			}
			arg = arg->next;
		}
	}
	return (0);
}
