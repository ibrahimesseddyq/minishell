/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/24 00:03:49 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		expanded_arg = ft_expand(lst->arg, env);
		// printf("expanded arg %s\n", expanded_arg);
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
	splitted_args = ft_split_quotes(expanded_string,*get_splitted_char(1));
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
	// second_splitted = remove_empty_strings(second_splitted, ast->t_cmd.args_size, &new_size);
	return (second_splitted);
}

void	choose_splitting_delimiter(t_arg_node	*lst, t_astnode *ast)
{
	t_arg_node	*tmp;

	tmp = lst;
	//TO FIX
	while (tmp)
	{
		// printf("------- lst-> [%s]------\n", lst->arg);
		tmp = tmp->next;
	}
	which_to_split_with(list_to_array(lst, ast), 1);
	which_to_split_with(list_to_array(lst, ast), 2);
}

int	execute_command_withargs(t_astnode *ast, t_lst *env, char **real_args)
{
	int	result;

	if (is_builtin_command(real_args[0]))
		result = execute_builtin(real_args, ast, env);
	else
		result = execute_external(real_args, ast, env);
	printf("exit status here is [%d]\n", ft_exit(127, GET_EXIT_STATUS));
	return (result);
}

int	exec_cmd(t_astnode *ast, t_lst *env)
{
	t_arg_node	*lst;
	char		**real_args;
	char		*cmd_path;
	t_arg_node	*tmp;

	(1) && (lst = ast->t_cmd.args, tmp = lst);
	while (tmp)
	{
		// printf("tmp [%s]\n", tmp->arg);
		tmp = tmp->next;
	}
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
	if (builtins_error(real_args) || !real_args)
		return (0);
	cmd_path = arg_cmds(real_args[0], env);
	if (cmd_path)
		real_args[0] = cmd_path;
	else
		return (write(2, "command not found\n", 19),
			ft_exit(127, SET_EXIT_STATUS), 127);
	return (execute_command_withargs(ast, env, real_args));
}
