/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/13 16:59:41 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"
#include <dirent.h>
#include <fnmatch.h>

#define INITIAL_ARRAY_SIZE 10
#define ARRAY_INCREMENT 10

static void replace_node_args(t_arg_node **node, char **expanded_args, int count)
{
    t_arg_node *current = *node;
    t_arg_node *prev = NULL;
    t_arg_node *new_node;
    int i;

    // Free the original node(s)
    while (current)
    {
        t_arg_node *temp = current;
        current = current->next;
        free(temp->arg);
        free(temp);
    }

    // Create and link new nodes with expanded arguments
    for (i = 0; i < count; i++)
    {
        new_node = (t_arg_node *)malloc(sizeof(t_arg_node));
        if (!new_node)
        {
            perror("malloc");
            // Free any previously allocated nodes
            while (i-- > 0)
            {
                free(expanded_args[i]);
            }
            free(expanded_args);
            return;
        }
        new_node->arg = expanded_args[i];
        new_node->next = NULL;
        if (prev)
        {
            prev->next = new_node;
        }
        else
        {
            *node = new_node; // Update the head of the list
        }
        prev = new_node;
    }

    // Ensure the list is terminated
    if (prev)
    {
        prev->next = NULL;
    }
}

void expand_wildcards_in_list(t_arg_node *args)
{
    DIR *dir;
    struct dirent *entry;
    t_arg_node *current = args;
    t_arg_node *next_node;
    char **expanded_args;
    int expanded_count;
    int array_size;
    int i;

    while (current)
    {
        next_node = current->next;  // Save the next node before potentially modifying the list

        // If argument contains wildcard '*'
        if (strchr(current->arg, '*'))
        {
            // Open the current directory
            dir = opendir(".");
            if (!dir)
            {
                perror("opendir");
                return;
            }

            // Initialize expanded_args and count
            array_size = INITIAL_ARRAY_SIZE;
            expanded_args = malloc(array_size * sizeof(char *));
            if (!expanded_args)
            {
                perror("malloc");
                closedir(dir);
                return;
            }
            expanded_count = 0;

            // Read directory entries
            while ((entry = readdir(dir)) != NULL)
            {
                if (fnmatch(current->arg, entry->d_name, 0) == 0)
                {
                    // Resize the array if needed
                    if (expanded_count >= array_size)
                    {
                        array_size += ARRAY_INCREMENT;
                        char **new_expanded_args = realloc(expanded_args, array_size * sizeof(char *));
                        if (!new_expanded_args)
                        {
                            perror("realloc");
                            closedir(dir);
                            // Free previously allocated strings
                            for (i = 0; i < expanded_count; i++)
                                free(expanded_args[i]);
                            free(expanded_args);
                            return;
                        }
                        expanded_args = new_expanded_args;
                    }

                    expanded_args[expanded_count] = strdup(entry->d_name);
                    if (!expanded_args[expanded_count])
                    {
                        perror("strdup");
                        closedir(dir);
                        // Free previously allocated strings
                        for (i = 0; i < expanded_count; i++)
                            free(expanded_args[i]);
                        free(expanded_args);
                        return;
                    }
                    expanded_count++;
                }
            }
            closedir(dir);

            // If no matches found, keep the original wildcard argument
            if (expanded_count == 0)
            {
                expanded_args[0] = strdup(current->arg);
                expanded_count = 1;
            }

            // Replace the node's arguments with expanded arguments
            replace_node_args(&current, expanded_args, expanded_count);

            // Free the expanded_args array (only the array, not the strings it points to)
            free(expanded_args);

            // Update the next_node after replacement to ensure it points to the correct node
            next_node = current->next;
        }

        current = next_node;  // Move to the next node in the list
    }

}



static char *arg_cmds(char *cmd, t_lst *env)
{
    char **path;
    char *tmp;

    // Check if cmd is already a full path or a built-in command
    if (cmd[0] == '/' || cmd[0] == '.' || 
        !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || 
        !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") || 
        !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export"))
    {
        return strdup(cmd);
    }

    path = ft_split(get_env(env, "PATH"), ':');
    if (!path)
        return strdup(cmd);  // If PATH is not set, return the command as is

    char *cmd_with_slash = ft_strjoin("/", cmd);

    if (!cmd_with_slash)
    {
        // Free path array
        for (int i = 0; path[i]; i++)
            free(path[i]);
        free(path);
        return strdup(cmd);
    }

    for (int i = 0; path[i]; i++)
    {
        tmp = ft_strjoin(path[i], cmd_with_slash);
        if (!tmp)
            continue;
        if (access(tmp, F_OK | X_OK) == 0)
        {
            // Free path array and cmd_with_slash
            for (int j = 0; path[j]; j++)
                free(path[j]);
            free(path);
            free(cmd_with_slash);
            return tmp;
        }
        free(tmp);
    }

    // Free path array and cmd_with_slash
    for (int i = 0; path[i]; i++)
        free(path[i]);
    free(path);
    free(cmd_with_slash);

    return strdup(cmd);  // If not found in PATH, return the command as is
}
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
	envp = malloc(sizeof(char *) * (size + 1));
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

char	**list_to_array(t_arg_node *lst, int size)
{
	char	**array;
	int		i;

	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		array[i] = ft_strdup(get_node_at(lst, i)->arg);
		i++;
	}
	array[i] = NULL;
	return (array);
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
    free(tmp);

    char **result = malloc(sizeof(char *) * (count + 1));
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
    free(tmp);

    return result;
}
int exec_cmd(t_astnode *ast, t_st *st, t_lst *env)
{
    int pid;
    int exit_status;
    t_arg_node *cmd;

    exit_status = 0;
    cmd = ast->t_cmd.args;
    if (!cmd || !get_node_at(ast->t_cmd.args, 0)->arg)
        return (0);

    // Expand all arguments
    int i = 0;
    while (get_node_at(ast->t_cmd.args, i))
    {
		char *expanded_arg = ft_expand(get_node_at(ast->t_cmd.args, i)->arg, env);
        free(get_node_at(ast->t_cmd.args, i)->arg);
        get_node_at(ast->t_cmd.args, i)->arg = expanded_arg;
        i++;
    }

    // Split the first argument if it contains spaces
    char **split_cmd = ft_split(get_node_at(ast->t_cmd.args, 0)->arg, ' ');
    if (split_cmd && split_cmd[0])
    {
        free(get_node_at(ast->t_cmd.args, 0)->arg);
        get_node_at(ast->t_cmd.args, 0)->arg = strdup(split_cmd[0]);

        // Insert additional arguments
        t_arg_node *current = ast->t_cmd.args;
        for (int j = 1; split_cmd[j]; j++)
        {
            t_arg_node *new_node = malloc(sizeof(t_arg_node));
            new_node->arg = strdup(split_cmd[j]);
            new_node->next = current->next;
            current->next = new_node;
            current = new_node;
            ast->t_cmd.args_size++; // Increase the argument count
        }

        // Free the split_cmd array
        for (int j = 0; split_cmd[j]; j++)
            free(split_cmd[j]);
        free(split_cmd);
    }

    // Convert the argument list to an array
    char **arg_cmd = list_to_array(ast->t_cmd.args, ast->t_cmd.args_size);
    if (!arg_cmd)
    {
        perror("malloc");
        return (1);
    }

    // Replace the first argument with its executable path
    char *cmd_path = arg_cmds(arg_cmd[0], env);
    if (cmd_path)
    {
        free(arg_cmd[0]);
        arg_cmd[0] = cmd_path;
    }

    pid = fork();
	printf("args\n");
	for(int i =0;arg_cmd[i];i++)
	{
		printf("arg_cmd[i]= %s\n",arg_cmd[i]);
	}
    if (pid == 0)
    {
        ft_redirection(ast);
        if (!ft_strcmp(arg_cmd[0], "cd"))
            ft_cd(ast->t_cmd.args_size, arg_cmd, 88, env);
        else if (!ft_strcmp(arg_cmd[0], "echo"))
            ft_echo(arg_cmd);
        else if (!ft_strcmp(arg_cmd[0], "pwd"))
            printf("%s\n", ft_pwd());
        else if (!ft_strcmp(arg_cmd[0], "env"))
            ft_env(env);
        else if (!ft_strcmp(arg_cmd[0], "exit"))
            my_exit(arg_cmd, ast->t_cmd.args_size);
        else if (!ft_strcmp(arg_cmd[0], "export"))
            ft_export(arg_cmd[1], env);
        else
        {
            char **envp = build_envp(env);
            if (!envp)
            {
                free(arg_cmd);
                ft_exit(1, SET_EXIT_STATUS);
            }
            exit_status = execve(arg_cmd[0], arg_cmd, envp);
            if (exit_status == -1)
            {
                printf("minishell: %s: command not found\n", arg_cmd[0]);
                ft_exit(127, SET_EXIT_STATUS);
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

    // Free the arg_cmd array
    for (i = 0; arg_cmd[i]; i++)
        free(arg_cmd[i]);
    free(arg_cmd);

    return (1);
}