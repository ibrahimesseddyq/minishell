#include "../minishell.h"
#include "../frontend/frontend.h"

// static char	*arg_cmds(char *cmd)
// {
// 	char **path;
// 	char *tmp;

// 	path = ft_split(getenv("PATH"), ':');
// 	cmd = ft_strjoin("/", cmd);
// 	while (path && *path)
// 	{
// 		tmp = ft_strjoin(*path, cmd);
// 		if (access(tmp, F_OK) == 0)
// 			return(tmp);			
// 		else
// 			free(tmp);
// 		path++;
// 	}
// 	return (NULL);
// }

void exec_pip(t_astnode *ast)
{
	int		i;
	int		j;
	int		pipfd[2];
	int		pid;
	int		pid2;
	// char	**cmd1;
	// char	**cmd2;
	i = 0;
	j = 0;
	// printf("%d\n", ast->type);
	// exit(1);
	// cmd1 = ast->binary.left->t_cmd.args;
	// cmd2 = ast->binary.right->t_cmd.args;
	// char *arg_cmd1[] = {arg_cmds(cmd1[0]), cmd1[1], NULL};
	// char *arg_cmd2[] = {arg_cmds(cmd2[0]), cmd2[1], NULL};

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipfd[1], 1);
		close(pipfd[0]);
		exec_cmd_line(ast->binary.left);
		exit(0);
		// if (execve(arg_cmds(cmd1[0]), arg_cmd1, NULL) == -1)
		// {
		// 	write(2, "Error\nexecve1()!!!\n", 19);
		// 	exit(1);
		// }
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipfd[0], 0);
		close(pipfd[1]);
		exec_cmd_line(ast->binary.right);
		exit(0);
		// if (execve(arg_cmds(cmd2[0]), arg_cmd2, NULL) == -1)
		// {
		// 	write(2, "Error\nexecve2()!!!\n", 19);
		// 	exit(1);
		// }
	}
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
}
