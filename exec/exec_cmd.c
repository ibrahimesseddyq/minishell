/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/27 02:31:00 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**generate_final_args(t_astnode *ast, t_lst *env, t_arg_node *lst)
{
	char		**second_splitted;

	second_splitted = generate_final_splitted(ast, env, lst);
	if (!second_splitted)
		return (NULL);
	second_splitted = make_array(second_splitted, ast->t_cmd.args_size);
	return (second_splitted);
}

int	execute_command_withargs(t_astnode *ast, t_lst *env, char **real_args)
{
	int	result;

	if (!real_args)
		return (0);
	if (is_builtin_command(real_args[0]))
		result = execute_builtin(real_args, ast, env);
	else
		result = execute_external(real_args, ast, env);
	return (result);
}

int	execute(t_astnode *ast, t_lst *env, char **real_args, char *cmd_path)
{
	if (cmd_path && real_args)
		real_args[0] = cmd_path;
	else
		return (write(2, "command not found\n", 19),
			ft_exit(127, SET_EXIT_STATUS), 127);
	return (execute_command_withargs(ast, env, real_args));
}

char	**return_true_cmd(void)
{
	char	**args;

	args = gcalloc(sizeof(char *) * 2);
	args[0] = ft_strdup("true");
	args[1] = NULL;
	return (args);
}

int	exec_cmd(t_astnode *ast, t_lst *env)
{
	t_arg_node	*lst;
	char		**real_args;
	char		*cmd_path;

	(1) && (lst = ast->t_cmd.args, cmd_path = NULL);
	real_args = NULL;
	if (no_command_case(&lst, env, ast))
		return (1);
	if (!lst)
		return (0);
	choose_splitting_delimiter(lst, ast);
	if (lst && !ft_strcmp(lst->arg, "true"))
		ast->t_cmd.args = lst;
	real_args = generate_final_args(ast, env, lst);
	remove_ampersand_strings(real_args, &(ast->t_cmd.args_size));
	if (real_args && !real_args[0])
		real_args[0] = ft_strdup("true");
	if (real_args && real_args[0] && real_args[0][0])
	{
		if (special_cases(real_args[0]))
			return (0);
		cmd_path = check_if_in_paths(real_args[0], env);
	}
	return (execute(ast, env, real_args, cmd_path));
}
