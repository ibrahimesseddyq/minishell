#include "../minishell.h"
#include "../frontend/frontend.h"
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>
#include <glob.h>

int	execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int stdout_backup;

	stdout_backup = ft_redirection(ast, env, 1);
	if (stdout_backup == -2)
			return (-2);
	if (!ft_strcmp(arg_cmd[0], "echo"))
		ft_echo(arg_cmd);
	else if (!ft_strcmp(arg_cmd[0], "cd"))
		ft_cd(ast->t_cmd.args_size + 1, arg_cmd, SET_EXIT_STATUS, env);
	else if (!ft_strcmp(arg_cmd[0], "pwd"))
		printf("%s\n", ft_pwd());
	else if (!ft_strcmp(arg_cmd[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(arg_cmd[0], "exit"))
		my_exit(arg_cmd, ast->t_cmd.args_size);
	else if (!ft_strcmp(arg_cmd[0], "export"))
		ft_export(arg_cmd, env);
	else if (!ft_strcmp(arg_cmd[0], "unset"))
		unset(arg_cmd, env);
	dup2(stdout_backup, 1);
	close(stdout_backup);
	return (1);
}

int check_file(char **argv)
{
	int is_abs_rel;

	is_abs_rel = 0;
	if(is_relative_absolute(argv[0]))
		is_abs_rel = 1;
	if(access(argv[0], F_OK) == -1)
	{
		if(is_abs_rel)
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
	return (!ft_strcmp((char *)cmd, "echo") || !ft_strcmp((char *)cmd, "cd") ||
			!ft_strcmp((char *)cmd, "pwd") || !ft_strcmp((char *)cmd, "env") ||
			!ft_strcmp((char *)cmd, "exit") || !ft_strcmp((char *)cmd, "export")
			|| !ft_strcmp((char *)cmd, "unset"));
}