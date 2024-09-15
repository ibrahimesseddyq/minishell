/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/15 00:09:26 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>
#include <glob.h>


char		**expand_wildcard(const char *pattern);
int			count_args(char **args);
int			is_builtin_command(const char *cmd);
int			execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env);
int			execute_external(char **arg_cmd, t_astnode *ast, t_lst *env);
char		*find_command_in_path(const char *cmd, char **path_dirs);
t_arg_node	*get_node_at(t_arg_node *lst, int pos);
void		expand_arguments(t_astnode *ast, t_lst *env);

void expand_arguments(t_astnode *ast, t_lst *env)
{
	int i = 0;
	t_arg_node *current = ast->t_cmd.args;
	t_arg_node *head = current;
	char *expanded_arg;

	while (current)
	{
		expanded_arg = ft_expand(current->arg, env);
		if (expanded_arg[0] != '"' && expanded_arg[0] != '\'')
		{
			char **split_args = split_string(expanded_arg);

			if (split_args)
			{
				t_arg_node *last_new_node = replace_node_args(current, split_args, count_args(split_args));
				if (head == current)
				{
					head = last_new_node;
				}
				current = last_new_node->next; 
				i += count_args(split_args);
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

int execute_external(char **arg_cmd, t_astnode *ast, t_lst *env)
{
	int pid = fork();
	int fd;
	int stdout_backup = dup(1);  
	if (pid == 0)
	{

		fd = ft_redirection(ast, env, 1);
		if (fd == -2)
			return (-2);
 
		char **envp = build_envp(env);
		if (!envp)
			exit(1);
		if (!check_file(arg_cmd))
		{
			close(fd);
			exit(127);
		}

		if(execve(arg_cmd[0], arg_cmd, envp) == -1)
		{
			handle_exec_error(arg_cmd[0]);
			exit(1);
		}
		exit(0);
	}
	else if (pid > 0)
	{
		int child_status;
		waitpid(pid, &child_status, 0);
		dup2(stdout_backup, 1);
		close(stdout_backup); 
		if (fd != stdout_backup)
			close(fd);

		if (WIFEXITED(child_status))
			ft_exit (WEXITSTATUS(child_status), SET_EXIT_STATUS);
		else if (WIFSIGNALED(child_status))
			ft_exit(128 + WTERMSIG(child_status), SET_EXIT_STATUS);
	}
	else 
	{
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

char **make_array(char **args, int size)
{
	for (int i = 0; i <= size && args[i]; i++)
	{

		char *str = args[i];
		for (int j = 0; str[j]; j++) {
			if (str[j] == *get_splitted_char(2))
			{
				str[j] = ' ';
			}
		}
	}
	return args;
}



int builtins_error(char **argv)
{
	int i;
	int command;

	i = 0;
	if (ft_strcmp(argv[0], "export") == 0)
		command = IS_EXPORT;
	while(argv[i])
	{
		if(command == IS_EXPORT && check_export_errors(argv[i]))
		{
			ft_exit(1, SET_EXIT_STATUS);
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
int special_cases( t_arg_node *lst)
{

	if (!ft_strcmp(lst->arg, "."))
	{
		fprintf(stderr, "filename argument required\n");
		ft_exit(2, SET_EXIT_STATUS);
		return (1);
	}
	else if (!ft_strcmp(lst->arg, ".."))
	{
		fprintf(stderr, "Command not found\n");
		ft_exit(127, SET_EXIT_STATUS);
		return (1);
	}
	else if (lst->arg[ft_strlen(lst->arg) - 1] == '/')
	{
		fprintf(stderr, "Is a directory\n");
		ft_exit(126, SET_EXIT_STATUS);
		return (1);
	}
	return (0);
}
 int no_command_case(t_arg_node *lst, t_lst *env, t_astnode *ast)
 {
	int stdout_backup;

	if(!lst)
	{
		stdout_backup = ft_redirection(ast, env, 0);
		if (stdout_backup == -2)
			return (-2);
		close(stdout_backup);
	}

	return (0);
 }
 int initial_builtin_errors(t_arg_node * args)
 {
	char *cmd;
	t_arg_node *arg;
	t_arg_node *tmp;

	cmd = args->arg;
	tmp = args;
	
	if((!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")))
	{
		arg = args->next;
		while(arg)
		{
			if(!ft_strcmp(arg->arg, "\"\"") || !ft_strcmp(arg->arg, "\'\'"))
			{
				write(2, "invalid identifier\n", 20);
				ft_exit(257, SET_EXIT_STATUS);
			}
			arg = arg->next;
		}
	}
	return (0);
 }
int exec_cmd(t_astnode *ast, t_lst *env)
{
	char *expanded_string;
	t_arg_node *lst;
	int i;

	lst = ast->t_cmd.args;
	i = 0;
	initial_builtin_errors(lst);
	if (no_command_case(lst, env, ast))
		return (1);
	if (!ast->t_cmd.args || !get_node_at(ast->t_cmd.args, 0)->arg)
		return (0);
	if (special_cases(lst))
		return (0);
	which_to_split_with(list_to_array(lst), 1);
	which_to_split_with(list_to_array(lst), 2);
	expanded_string = ft_strdup("");
	while (i <= ast->t_cmd.args_size)
	{
		char *expanded_arg = ft_expand(lst->arg, env);
		char *temp = ft_strjoin(expanded_string, expanded_arg);
		expanded_string = temp;
		if (lst->next)
		{
			temp = ft_strjoin(expanded_string, ft_strdup(char_to_string(*get_splitted_char(1))));
			expanded_string = temp;
		}
		lst = lst->next;
		i++;
	}
	char **splitted_args = ft_split_quotes(expanded_string,*get_splitted_char(1));

	if (!splitted_args)
		return 0;

	char **second_splitted = split_all_strings(splitted_args, *get_splitted_char(2));

	char **real_args = make_array(second_splitted, ast->t_cmd.args_size);
	if (builtins_error(real_args))
		return (1);
	char *cmd_path = arg_cmds(real_args[0], env);
	if (cmd_path)
		real_args[0] = cmd_path;
	else
	{
		fprintf(stderr, "minishell: %s: command not found\n", real_args[0]);
		ft_exit(127, SET_EXIT_STATUS);
		return (127);
	}
	int result;
	if (is_builtin_command(real_args[0]))
		result = execute_builtin(real_args, ast, env);
	else
		result = execute_external(real_args, ast, env);
}