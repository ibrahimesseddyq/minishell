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

int exec_cmd(int ac, char *av[])
{
	int		i;
	int		j;
	int		pipfd[2];
	int		pid;
	char	**cmd1;
	i = 0;
	j = 0;

    (void)av;
	cmd1 = ft_split(av[2], ' ');
	char *arg_cmd1[] = {arg_cmds(cmd1[0]), cmd1[1], NULL};
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
		close(pipfd[1]);
		close(pipfd[0]);
		waitpid(pid, NULL, 0);
	}else
		printf("the file not exist!!!\n");	
	return(0);
}