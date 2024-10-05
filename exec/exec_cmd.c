/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/05 10:58:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*get_expanded_string(t_lst *env, t_arg_node *lst)
{
	char *exp_str_empty;
	char *expanded_str;

	exp_str_empty = NULL;
	expanded_str = ft_expand(lst->arg, env);
	if (!ft_strcmp(lst->arg, "\"\"") || !ft_strcmp(lst->arg, "\'\'") || !expanded_str[0])
	{
		exp_str_empty = (char *)gcalloc(2);
		exp_str_empty[0] = *get_splitted_char(3);
		exp_str_empty[1] = '\0';
		return (exp_str_empty);
	}
	else
		return (expanded_str);
}

char	*expand_wd(char *expanded_arg)
{
	char *pattern[] = {"*", "*.c", NULL}; // Searching all files in first level, then all .c files in second level
	char **found_files = NULL;
	int found_count = 0;
	t_wildcard_data data;
	char *pwd = "."; // Current directory

	pattern[0] = ft_strdup(expanded_arg);
	pattern[1] = ft_strdup("");
	data.pattern = pattern;
	data.found_files = &found_files;
	data.found_count = &found_count;
	return (expand_wildcard(pwd, 0, &data));
}

char	*expand_wd_redir(char *expanded_arg)
{
	char *pattern[] = {"*", "*.c", NULL}; // Searching all files in first level, then all .c files in second level
	char **found_files = NULL;
	int found_count = 0;
	t_wildcard_data data;
	char *pwd = "."; // Current directory

	pattern[0] = ft_strdup(expanded_arg);
	pattern[1] = ft_strdup("");
	data.pattern = pattern;
	data.found_files = &found_files;
	data.found_count = &found_count;
	return (expand_wildcard(pwd, 0, &data));
}

char	**generate_final_splitted(t_astnode *ast, t_lst *env, t_arg_node *lst)
{
	int			i;
	char		*expanded_string;
	char		**splitted_args;
	char		*expanded_arg;
	char		*temp;
	t_arg_node	*head;

	(1) && (expanded_string = ft_strdup(""), head = lst, i = 0, lst = head);
	while (i <= ast->t_cmd.args_size)
	{
		// printf("lst->arg %s\n", lst->arg);
		expanded_arg = get_expanded_string(env, lst);
		// printf("expanded ard [%s]\n", expanded_arg);
		expanded_arg = expand_wd(expanded_arg);
		temp = ft_strjoin(expanded_string, expanded_arg);
		expanded_string = temp;
		if (lst->next)
		{
			temp = ft_strjoin(expanded_string,
					ft_strdup(char_to_string(*get_splitted_char(1))));
			expanded_string = temp;
		}
		// printf("expanded string %s\n", expanded_string);
		lst = lst->next;
		i++;
	}
	lst = head;
	splitted_args = ft_split_quotes(expanded_string, *get_splitted_char(1));
	if (!splitted_args)
		return (0);
	// printf("ast->t_cmd.args_size %d\n", ast->t_cmd.args_size);
	// printf("splitted char 1 [%c] splitted char 2 [%c]\n", *get_splitted_char(1), *get_splitted_char(2));
	ast->t_cmd.args_size = i;
	return (split_all_strings(splitted_args, *get_splitted_char(2)));
}

char	**generate_final_args(t_astnode *ast, t_lst *env, t_arg_node *lst)
{
	char		**second_splitted;
	t_arg_node	*tmp;

	tmp = lst;
	while (tmp)
	{
		// printf("tmp2 [%s]\n", tmp->arg);
		tmp = tmp->next;
	}
	second_splitted = generate_final_splitted(ast, env, lst);
	if (!second_splitted)
		return (NULL);
	// for (int i = 0; second_splitted[i]; i++)
	// {
	// 	printf("seccond splitted [%s]\n", second_splitted[i]);
	// }
	second_splitted = make_array(second_splitted, ast->t_cmd.args_size);
	// for (int i = 0; second_splitted[i]; i++)
	// {
	// 	printf("seccond splitted [%s]\n", second_splitted[i]);
	// }
	return (second_splitted);
}

void	choose_splitting_delimiter(t_arg_node	*lst, t_astnode *ast)
{
	t_arg_node	*tmp;

	tmp = lst;
	//TO FIX
	while (tmp)
	{
		tmp = tmp->next;
	}
	which_to_split_with(list_to_array(lst, ast), 1);
	which_to_split_with(list_to_array(lst, ast), 2);
	which_to_split_with(list_to_array(lst, ast), 3);
}

int	execute_command_withargs(t_astnode *ast, t_lst *env, char **real_args)
{
	int	result;

	// for (int i=0; real_args[i]; i++)
	// {
	// 	printf("args is [%s]\n", real_args[i]);
	// }
	if (is_builtin_command(real_args[0]))
		result = execute_builtin(real_args, ast, env);
	else
		result = execute_external(real_args, ast, env);
	return (result);
}

int	exec_cmd(t_astnode *ast, t_lst *env)
{
	t_arg_node	*lst;
	char		**real_args;
	char		*cmd_path;
	t_arg_node	*tmp;

	(1) && (lst = ast->t_cmd.args, tmp = lst);
	// printf("execcmd\n");
	initial_builtin_errors(lst);
	if (no_command_case(lst, env, ast))
		return (1);
	if (!ast->t_cmd.args || !get_node_at(ast->t_cmd.args, 0)->arg)
		return (0);
	if (special_cases(lst))
		return (0);
	choose_splitting_delimiter(lst, ast);
	tmp = lst;
	real_args = generate_final_args(ast, env, lst);
	if (!real_args)
		return (0);
	cmd_path = arg_cmds(real_args[0], env);
	// for (int i = 0; real_args[i]; i++)
	// {
	// 	printf("real_args [%s]\n", real_args[i]);
	// }
	if (cmd_path)
		real_args[0] = cmd_path;
	else
		return (write(2, "command not found 1 \n", 19),
			ft_exit(127, SET_EXIT_STATUS), 127);
	return (execute_command_withargs(ast, env, real_args));
}
