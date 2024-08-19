/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/19 10:17:18 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>
#include <glob.h>

#define INITIAL_ARRAY_SIZE 10
#define ARRAY_INCREMENT 10
char		**expand_wildcard(const char *pattern);
int			count_args(char **args);
int			is_builtin_command(const char *cmd);
int			execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env);
int			execute_external(char **arg_cmd, t_astnode *ast, t_lst *env);
char		*find_command_in_path(const char *cmd, char **path_dirs);
t_arg_node	*get_node_at(t_arg_node *lst, int pos);
void		expand_arguments(t_astnode *ast, t_lst *env);
static int	count_env_vars(t_lst *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
static char	**build_envp(t_lst *env)
{
	char	**envp;
	int		size;
	int		i;
	char	*var;

	size = count_env_vars(env);
	envp = gcalloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		var = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		envp[i++] = var;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void handle_exec_error(const char *cmd)
{
    if (errno == EACCES) {
        fprintf(stderr, "minishell: %s: Permission denied\n", cmd);
        ft_exit(126, SET_EXIT_STATUS);
    } else if (errno == ENOENT) {
        fprintf(stderr, "minishell: %s: No such file or directory\n", cmd);
        ft_exit(127, SET_EXIT_STATUS);
    } else if (errno == ENOTDIR) {
        fprintf(stderr, "minishell: %s: Not a directory\n", cmd);
        ft_exit(126, SET_EXIT_STATUS);
    } else if (errno == ENOEXEC) {
        fprintf(stderr, "minishell: %s: Exec format error\n", cmd);
        ft_exit(126, SET_EXIT_STATUS);
    } else if (errno == E2BIG) {
        fprintf(stderr, "minishell: %s: Argument list too long\n", cmd);
        ft_exit(126, SET_EXIT_STATUS);
    } else if (errno == ENOMEM) {
        fprintf(stderr, "minishell: %s: Out of memory\n", cmd);
        ft_exit(126, SET_EXIT_STATUS);
    } else if (errno == ETXTBSY) {
        fprintf(stderr, "minishell: %s: Text file busy\n", cmd);
        ft_exit(126, SET_EXIT_STATUS);
    } else {
        fprintf(stderr, "minishell: %s: Error executing command (%s)\n", cmd, strerror(errno));
        ft_exit(126, SET_EXIT_STATUS);
    }
}

static void replace_node_args(t_arg_node **node, char **expanded_args, int count)
{
    t_arg_node *prev = NULL;
    t_arg_node *new_node;
    int i;

    for (i = 0; i < count; i++)
    {
        new_node = (t_arg_node *)gcalloc(sizeof(t_arg_node));
        if (!new_node)
        {
            perror("gcalloc");
            return;
        }
        new_node->arg = expanded_args[i];
        new_node->next = NULL;
        if (prev)
            prev->next = new_node;
        else
            *node = new_node;
        prev = new_node;
    }
    if (prev)
        prev->next = NULL;
}
 
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void expand_wildcards_in_list(t_arg_node *args)
{
    t_arg_node *current = args;
    while (current)
    {
        if (strchr(current->arg, '*'))
        {
            char **expanded_args = expand_wildcard(current->arg);
            if (expanded_args && expanded_args[0])
            {
                replace_node_args(&current, expanded_args, count_args(expanded_args));
            }
        }
        current = current->next;
    }
}
char **split_string(char *str)
{
    int count = 0;
    char *tmp = strdup(str);
    char *token = strtok(tmp, " ");
    while (token)
    {
        count++;
        token = strtok(NULL, " ");
    }

    char **result = gcalloc(sizeof(char *) * (count + 1));
    if (!result)
        return NULL;

    int i = 0;
    tmp = strdup(str);
    token = strtok(tmp, " ");
    while (token)
    {
        result[i] = strdup(token);
        i++;
        token = strtok(NULL, " ");
    }
    result[i] = NULL;

    return result;
}

char **expand_wildcard(const char *pattern)
{
    glob_t globbuf;
    char **result = NULL;

    if (glob(pattern, GLOB_NOCHECK, NULL, &globbuf) == 0)
    {
        result = gcalloc(sizeof(char *) * (globbuf.gl_pathc + 1));
        for (size_t i = 0; i < globbuf.gl_pathc; i++)
        {
            result[i] = ft_strdup(globbuf.gl_pathv[i]);
        }
        result[globbuf.gl_pathc] = NULL;
    }

    globfree(&globbuf);
    return result;
}

char *arg_cmds(char *cmd, t_lst *env)
{
    if (cmd[0] == '/' || cmd[0] == '.' || is_builtin_command(cmd))
        return ft_strdup(cmd);

    char *path = get_env(env, "PATH");
    if (!path)
        return ft_strdup(cmd);

    char **path_dirs = ft_split(path, ':');
    if (!path_dirs)
        return ft_strdup(cmd);

    char *cmd_path = find_command_in_path(cmd, path_dirs);
    return cmd_path ? cmd_path : ft_strdup(cmd);
}
void expand_arguments(t_astnode *ast, t_lst *env)
{
    int i = 0;
    t_arg_node *current = ast->t_cmd.args;
    char *expanded_arg;

    while (current)
    {
        expanded_arg = ft_expand(current->arg, env);
        if (expanded_arg[0] != '"' && expanded_arg[0] != '\'')
        {
            char **split_args = split_string(expanded_arg);
            for(int i=0; split_args[i]; i++)
            {
                printf("argument %s\n",split_args[i]);
            }
            if (split_args)
            {
                t_arg_node *next_node = current->next;
                replace_node_args(&current, split_args, count_args(split_args));
                i += count_args(split_args);
                current = next_node;
            }
            else
            {
                current = current->next;
            }
        }
        else
        {
            current->arg = expanded_arg;
            current = current->next;
            i++;
        }
    }
    ast->t_cmd.args_size = i;
}
int	is_builtin_command(const char *cmd)
{
	return (!ft_strcmp((char *)cmd, "echo") || !ft_strcmp((char *)cmd, "cd") ||
			!ft_strcmp((char *)cmd, "pwd") || !ft_strcmp((char *)cmd, "env") ||
			!ft_strcmp((char *)cmd, "exit") || !ft_strcmp((char *)cmd, "export"));
}

int	execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	if (!ft_strcmp(arg_cmd[0], "echo"))
		return (ft_echo(arg_cmd), 0);
	else if (!ft_strcmp(arg_cmd[0], "cd"))
		return (ft_cd(ast->t_cmd.args_size, arg_cmd, SET_EXIT_STATUS, env));
	else if (!ft_strcmp(arg_cmd[0], "pwd"))
		return (printf("%s\n", ft_pwd()), 0);
	else if (!ft_strcmp(arg_cmd[0], "env"))
		return (ft_env(env), 0);
	else if (!ft_strcmp(arg_cmd[0], "exit"))
		return (my_exit(arg_cmd, ast->t_cmd.args_size));
	else if (!ft_strcmp(arg_cmd[0], "export"))
		return (ft_export(arg_cmd, env), 0);
	return (1);
}

int execute_external(char **arg_cmd, t_astnode *ast, t_lst *env)
{
    int pid = fork();
    if (pid == 0)
    {
        ft_redirection(ast);
        char **envp = build_envp(env);
        if (!envp)
            ft_exit(1, SET_EXIT_STATUS);

        if (access(arg_cmd[0], F_OK) == -1 || arg_cmd[0][0] == '\0')
        {
            fprintf(stderr, "minishell: %s: command not found\n", arg_cmd[0]);
            ft_exit(127, SET_EXIT_STATUS);
        }
        else
        {
            execve(arg_cmd[0], arg_cmd, envp);
            handle_exec_error(arg_cmd[0]);
        }
    }
    else if (pid > 0)
    {

        int child_status;
        waitpid(pid, &child_status, 0);
        if (WIFEXITED(child_status))
            ft_exit(WEXITSTATUS(child_status), SET_EXIT_STATUS);
        else if (WIFSIGNALED(child_status))
            ft_exit(128 + WTERMSIG(child_status), SET_EXIT_STATUS);
    }
    else
    {
                    printf("fork error\n");

        perror("fork");
        ft_exit(1, SET_EXIT_STATUS);
    }
    return 1;
}
char *find_command_in_path(const char *cmd, char **path_dirs)
{
    char *cmd_with_slash = ft_strjoin("/", (char *)cmd);
    if (!cmd_with_slash)
        return NULL;

    for (int i = 0; path_dirs[i]; i++)
    {
        char *full_path = ft_strjoin(path_dirs[i], cmd_with_slash);
        if (!full_path)
            continue;

        if (access(full_path, F_OK | X_OK) == 0)
            return full_path;
    }

    return NULL;
}




t_arg_node	*get_node_at(t_arg_node *lst, int pos)
{
	int			i;
	t_arg_node	*head;

	i = 0;
	head = lst;
	while (head)
	{
		if (i == pos)
			return (head);
		i++;
		head = head->next;
	}
	return (NULL);
}

char **list_to_array(t_arg_node *lst)
{
    int size = 0;
    t_arg_node *current = lst;

    while (current)
    {
        size++;
        current = current->next;
    }

    char **array = gcalloc(sizeof(char *) * (size + 1));
    if (!array)
        return NULL;

    current = lst;
    for (int i = 0; i < size; i++)
    {
        if (current)
        {
            array[i] = ft_strdup(current->arg);
            current = current->next;
        }
        else
            array[i] = NULL;
    }
    array[size] = NULL;

    return array;
}


int exec_cmd(t_astnode *ast, t_lst *env)
{
    if (!ast->t_cmd.args || !get_node_at(ast->t_cmd.args, 0)->arg)
        return 0;

    expand_arguments(ast, env);
    char **arg_cmd = list_to_array(ast->t_cmd.args);

    if (!arg_cmd)
        return 1;

    // Check if the command is stored in a variable
    if (arg_cmd[0][0] == '$')
    {
        char *cmd_var = arg_cmd[0] + 1;
        char *cmd_value = get_env(env, cmd_var);
        if (cmd_value)
        {
            // Split the command value into command and arguments
            char **cmd_parts = split_string(cmd_value);
            if (cmd_parts)
            {
                // Count the total number of arguments
                int total_args = count_args(cmd_parts) + count_args(arg_cmd) - 1;
                char **new_arg_cmd = gcalloc(sizeof(char *) * (total_args + 1));
                
                // Copy the command and its arguments
                int i = 0;
                while (cmd_parts[i])
                {
                    new_arg_cmd[i] = ft_strdup(cmd_parts[i]);
                    i++;
                }
                
                // Copy the remaining arguments
                int j = 1;
                while (arg_cmd[j])
                {
                    new_arg_cmd[i] = ft_strdup(arg_cmd[j]);
                    i++;
                    j++;
                }
                new_arg_cmd[i] = NULL;
                arg_cmd = new_arg_cmd;
            }
        }
    }

    char *cmd_path = arg_cmds(arg_cmd[0], env);
    if (cmd_path)
        arg_cmd[0] = cmd_path;

    if (is_builtin_command(arg_cmd[0]))
        return execute_builtin(arg_cmd, ast, env);
    else
        return execute_external(arg_cmd, ast, env);
}