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

int pipex(char **cmd1, char **cmd2)
{
int		i;
	int		j;
	int		pipfd[2];
	int		pid;
	int		pid2;
	char	**cmd1;
	char	**cmd2;
	i = 0;
	j = 0;

	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	char *arg_cmd1[] = {arg_cmds(cmd1[0]), cmd1[1], NULL};
	char *arg_cmd2[] = {arg_cmds(cmd2[0]), cmd2[1], NULL};
	if (access(av[1], R_OK) == 0)
	{
		pipe(pipfd);
		pid = fork();
		if (pid == 0)
		{
			int fd1 = open(av[1], O_RDONLY, 0644);
			dup2(pipfd[1], 1);
			dup2(fd1, 0);
			close(pipfd[0]);
			if (execve(arg_cmds(cmd1[0]), arg_cmd1, NULL) == -1)
			{
				write(2, "Error\nexecve1()!!!\n", 19);
				exit(1);
			}
		}
		pid2 = fork();
		if (pid2 == 0)
		{
			int fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd2 == -1)
			{
				printf("fd fail!!\n");
				exit(1);
			}
			dup2(pipfd[0], 0);
			dup2(fd2, 1);
			close(pipfd[1]);
				if (execve(arg_cmds(cmd2[0]), arg_cmd2, NULL) == -1)
				{
					write(2, "Error\nexecve2()!!!\n", 19);
					exit(1);
				}
		}
		close(pipfd[1]);
		close(pipfd[0]);
		waitpid(pid2, NULL, 0);
		waitpid(pid, NULL, 0);
	}else
		printf("the file not exist!!!\n");	
	return(0);
}