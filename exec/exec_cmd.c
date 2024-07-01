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
		{
			// ast->t_cmd.status = 1;
			return(tmp);
		}
		else
			free(tmp);
		path++;
	}
	return (NULL);
}

void exec_cmd(t_astnode *ast)
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
		// ast->t_cmd.status = 1;
		
    	// printf("1-> cmd---> %d\n", ast->t_cmd.status);
		if (execve(arg_cmds(cmd[0]), arg_cmd, NULL) == -1)
		{
			ast->t_cmd.status = 0;
			// printf("1-> cmd---> %d\n", ast->t_cmd.status);
			// printf("minishell: %s: command not found\n",cmd[0]);
			exit(1);
		}
		
	}
    waitpid(pid, &ast->t_cmd.status, 0);
	if (WIFEXITED(ast->t_cmd.status))
	{
		ast->t_cmd.st = WEXITSTATUS(ast->t_cmd.status);
		printf ("Child exited with status  : %d\n", ast->t_cmd.st);
	}else {
        printf("Child did not exit normally\n");
    }
}
