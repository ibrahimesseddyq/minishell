/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/16 17:31:10 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

char	**generate_final_splitted(t_astnode *ast, t_lst *env, t_arg_node *lst)
{
	int		i;
	char	*expanded_string;
	char	**splitted_args;
	char	*expanded_arg;
	char	*temp;
	t_arg_node *head;

	expanded_string = ft_strdup("");
	head = lst;
	i = 0;
	while(lst)
	{
		printf("[generate_final_splitted] lst %s\n", lst->arg);
		lst = lst->next;
	}
	lst = head;
	printf("[generate_final_splitted] i is %d\n", i);
	while (i <= ast->t_cmd.args_size)
	{
		expanded_arg = ft_expand(lst->arg, env);
		temp = ft_strjoin(expanded_string, expanded_arg);
		expanded_string = temp;
		if (lst->next)
		{
			temp = ft_strjoin(expanded_string,
					ft_strdup(char_to_string(*get_splitted_char(1))));
			expanded_string = temp;
			printf("[generate_final_splitted] expanded string %s\n", expanded_string);
		}
		lst = lst->next;
		i++;
	}
	lst = head;
	splitted_args = ft_split_quotes(expanded_string,*get_splitted_char(1));
	for (int i = 0;splitted_args[i]; i++)
	{
		printf("[generate_final_splitted] sec_splitted [%s]\n", splitted_args[i]);
	}
	if (!splitted_args)
		return (0);
	return (split_all_strings(splitted_args, *get_splitted_char(2)));
}

char	**generate_final_args(t_astnode *ast, t_lst *env, t_arg_node *lst)
{
	char		**second_splitted;
	t_arg_node *tmp;
	tmp = lst;
	while (tmp)
	{
		printf("lst [%s]\n", tmp->arg);
		tmp = tmp->next;
	}
	second_splitted = generate_final_splitted(ast, env, lst);
	for (int i = 0;second_splitted[i]; i++)
	{
		printf("sec_splitted [%s]\n", second_splitted[i]);
	}
	return (make_array(second_splitted, ast->t_cmd.args_size));
}

void	choose_splitting_delimiter(t_arg_node	*lst)
{
	which_to_split_with(list_to_array(lst), 1);
	which_to_split_with(list_to_array(lst), 2);
}

int	execute_command_withargs(t_astnode *ast, t_lst *env, char **real_args)
{
	int	result;

	if (is_builtin_command(real_args[0]))
		result = execute_builtin(real_args, ast, env);
	else
		result = execute_external(real_args, ast, env);
	return (result);
}

int	exec_cmd(t_astnode *ast, t_lst *env)
{
	t_arg_node	*lst;
	int			result;
	char		**real_args;
	char		*cmd_path;

	lst = ast->t_cmd.args;
	t_arg_node	*tmp = lst;
	while(tmp)
	{
		printf("arg is %s\n", tmp->arg);
		tmp = tmp->next;
	}
	initial_builtin_errors(lst);
	if (no_command_case(lst, env, ast))
		return (1);
	if (!ast->t_cmd.args || !get_node_at(ast->t_cmd.args, 0)->arg)
		return (0);
	if (special_cases(lst))
		return (0);
	choose_splitting_delimiter(lst);
	tmp = lst;
	while(tmp)
	{
		printf("arg 2 is %s\n", tmp->arg);
		tmp = tmp->next;
	}
	real_args = generate_final_args(ast, env, lst);
	for(int i = 0; real_args[i]; i++)
	{
		printf("arg3 is %s\n", real_args[i]);
	}
	if (builtins_error(real_args))
		return (1);
	cmd_path = arg_cmds(real_args[0], env);
	if (cmd_path)
		real_args[0] = cmd_path;
	else
		return (write(2, "command not found\n", 19),
			ft_exit(127, SET_EXIT_STATUS), 127);
	return (execute_command_withargs(ast, env, real_args));
}
