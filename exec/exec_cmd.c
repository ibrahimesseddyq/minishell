/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/03 05:38:13 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

void exec_cmd(t_astnode *ast, t_st *st,t_lst *env)
{
	int		i;
// 	int		j;
	int		pid;
	char	**cmd;

	i = 0;
	// j = 0;

	// cmd = NULL.args
	cmd = ast->t_cmd.args;

	if (!cmd || !cmd[0])
	{
		printf("command null\n");
		return ;
	}
	while (cmd[i])
	{
		cmd[i] = ft_expand(cmd[i], env);
		// printf("cmd[%d] = %s\n", i, cmd[i]);
		i++;
	}
	char *arg_cmd[] = {arg_cmds(cmd[0]), cmd[1], NULL};
	pid = fork();

	if (pid == 0)
	{
		// ft_red_in(ast);
		// ft_red_out(ast);
		ft_redirection(ast);
		if (!ft_strcmp(ast->t_cmd.args[0], "cd"))
		{
			
			printf("cd, args 0 [%s]\n", ast->t_cmd.args[0]);
			ft_cd(100,ast->t_cmd.args,88, env);
		}
		// else if(ft_strcmp(ast->t_cmd.args[0], "echo"))
		// {

		// }
		else if(!ft_strcmp(ast->t_cmd.args[0], "pwd"))
		{
			printf("%s\n", ft_pwd());	
		}
		// else if(ft_strcmp(ast->t_cmd.args[0], "exit"))
		// {
				
		// }
		else if (execve(arg_cmds(cmd[0]), arg_cmd, NULL) == -1)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			exit(127);
		}
	}
	waitpid(pid, &(st->status), 0);
	if (WIFEXITED(st->status))
		st->st = WEXITSTATUS(st->status);
}
