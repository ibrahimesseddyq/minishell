#include "../minishell.h"
#include "../frontend/frontend.h"

static char	*arg_cmds(char *cmd)
{
	char **path;
	char *tmp;

	path = ft_split(getenv("PATH"), ':');
	cmd = ft_strjoin("/", cmd);
	while (path && *path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (access(tmp, F_OK) == 0)
			return(tmp);
		else
			free(tmp);
		path++;
	}
	return (NULL);
}

void exec_cmd(t_astnode *ast, t_st *st)
{
	int		i;
	int		j;
	int		pid;
	char	**cmd;

	i = 0;
	j = 0;

	cmd = ast->t_cmd.args;
	char *arg_cmd[] = {arg_cmds(cmd[0]), cmd[1], NULL};
	pid = fork();
	if (pid == 0)
	{
		// if (ft_strcmp(ast->t_cmd.args[0], "cd"))
		// {
		// 	ft_cd();
		// }
		// else if(ft_strcmp(ast->t_cmd.args[0], "echo"))
		// {

		// }
		// else if(ft_strcmp(ast->t_cmd.args[0], "pwd"))
		// {
			
		// }
		// else if(ft_strcmp(ast->t_cmd.args[0], "exit"))
		// {
			
		// }
		if (execve(arg_cmds(cmd[0]), arg_cmd, NULL) == -1)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			exit(127);
		}
	}
	waitpid(pid, &(st->status), 0);
	if (WIFEXITED(st->status))
		st->st = WEXITSTATUS(st->status);
}
