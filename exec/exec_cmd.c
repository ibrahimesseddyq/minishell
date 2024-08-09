/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/09 12:46:14 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"

static char	*arg_cmds(char *cmd, t_lst *env)
{
	char **path;
	char *tmp;

	path = ft_split(get_env(env ,"PATH"), ':');
	cmd = ft_strjoin("/", cmd);
	while (path && *path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (access(tmp, F_OK) == 0)
			return(tmp);
		path++;
	}
	return (NULL);
}
static int count_env_vars(t_lst *env)
{
    int i;

    i = 0;
    while(env)
    {
        i++;
        env = env->next;
    }
    return i;
}
static char **build_envp(t_lst *env)
{
    char    **envp;
    int     size;
    int i;
    char *var;

    i = 0;
    size = count_env_vars(env);
    envp = malloc(sizeof(char *) * size);
    while(env)
    {
        var = ft_strjoin(ft_strjoin(env->key, "="), env->value);
        envp[i] = var;
        env = env->next;
    }
    return envp;
}
int exec_cmd(t_astnode *ast, t_st *st, t_lst *env)
{
    int i;
    int k;
    int pid;
    char **cmd;
    int exit_status;
    char **arg_cmd;
    char *command_name;
    

    exit_status = 0;
    i = 0;
    k = 1;
    cmd = ast->t_cmd.args;
    command_name = ft_strdup(ast->t_cmd.args[0]);
    if (!cmd || !cmd[0])
        return 0;

    while (cmd[i]) {
        cmd[i] = ft_expand(cmd[i], env);
        i++;
    }

    arg_cmd = malloc(sizeof(char *) * (ast->t_cmd.args_size));
    if (!arg_cmd) {
        perror("malloc");
        return 1;
    }

    while (k < ast->t_cmd.args_size) {
        arg_cmd[k - 1] = cmd[k];
        // printf("cmd[k] %s\n",cmd[k]);
        k++;
    }
    arg_cmd[ast->t_cmd.args_size - 1] = NULL; // NULL terminator

    cmd[0] = arg_cmds(cmd[0], env);

    pid = fork();
    if (pid == 0)
    {
        ft_redirection(ast);
        if (!ft_strcmp(command_name, "cd"))
            ft_cd(ast->t_cmd.args_size, cmd, 88, env);
        else if (!ft_strcmp(command_name, "echo"))
            ft_echo(cmd);
        else if (!ft_strcmp(command_name, "pwd"))
            printf("%s\n", ft_pwd());
        else if (!ft_strcmp(command_name, "env"))
		{

            ft_env(env);
		}
        else if (!ft_strcmp(command_name, "exit"))
        {
            my_exit(cmd, ast->t_cmd.args_size);
        }
        else if (!ft_strcmp(command_name, "export"))
        {
            ft_export(cmd[1], env);
        }
        else
        {
            char **envp = build_envp(env);
            exit_status = execve(cmd[0], cmd, envp);
            if (exit_status == -1)
            {
                printf("minishell: %s: command not found\n", cmd[0]);
                ft_exit(127, SET_EXIT_STATUS);
				return 0;
            }
            ft_exit(exit_status, SET_EXIT_STATUS);
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &(st->status), 0);
        if (WIFEXITED(st->status))
            st->st = WEXITSTATUS(st->status);
    }
    else
    {
        perror("fork");
        ft_exit(1, SET_EXIT_STATUS);
    }
    return 1;
}