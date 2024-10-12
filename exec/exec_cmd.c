/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:04 by ynachat           #+#    #+#             */
/*   Updated: 2024/10/12 22:19:18 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_expanding_of_argument(t_state_fs	*state, t_lst *env)
{
	if (star_inside_quotes(state->lst->arg))
		state->star_inside = 1;
	state->expanded_arg = get_expanded_string(env, state->lst);
	if (!state->star_inside)
		state->expanded_arg = expand_wd(state->expanded_arg);
	state->temp = ft_strjoin(state->expanded_string, state->expanded_arg);
	state->expanded_string = state->temp;
	if (state->lst->next)
	{
		state->temp = ft_strjoin(state->expanded_string,
				ft_strdup(char_to_string(*get_splitted_char(1))));
		state->expanded_string = state->temp;
	}
	state->lst = state->lst->next;
	state->i++;
	state->star_inside = 0;
}

char	**generate_final_splitted(t_astnode *ast, t_lst *env, t_arg_node *lst)
{
	t_state_fs	state;

	state.expanded_string = ft_strdup("");
	state.lst = lst;
	state.head = lst;
	state.i = 0;
	state.star_inside = 0;
	while (state.i <= ast->t_cmd.args_size)
	{
		handle_expanding_of_argument(&state, env);
	}
	state.lst = state.head;
	state.splitted_args
		= ft_split_quotes(state.expanded_string, *get_splitted_char(1));
	if (!state.splitted_args)
		return (0);
	ast->t_cmd.args_size = state.i;
	return (split_all_strings(state.splitted_args, *get_splitted_char(2)));
}

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

	if (is_builtin_command(real_args[0]))
		result = execute_builtin(real_args, ast, env);
	else
		result = execute_external(real_args, ast, env);
	return (result);
}
int	handle_redirs_when_empty(t_lst *env, t_astnode *ast)
{
	int	stdout_backup;

	stdout_backup = -1;

	stdout_backup = ft_redirection(ast, env, 0);
	if (stdout_backup == -2)
		return (-2);
	ft_close(&stdout_backup);
	return (0);
}
int	exec_cmd(t_astnode *ast, t_lst *env)
{
	t_arg_node	*lst;
	char		**real_args;
	char		*cmd_path;
	t_arg_node	*tmp;

	(1) && (lst = ast->t_cmd.args, tmp = lst);
	if (no_command_case(lst, env, ast))
		return (1);
	if (!ast->t_cmd.args || !get_node_at(ast->t_cmd.args, 0)->arg)
		return (0);
	choose_splitting_delimiter(lst, ast);
	tmp = lst;
	real_args = generate_final_args(ast, env, lst);
	real_args = handle_empty_var_beginning(real_args);
	
	if (!real_args || !real_args[0] || !real_args[0][0])
	{
		if (ast->t_cmd.redirections)
			handle_redirs_when_empty(env, ast);
		return (0);
	}
	if (special_cases(real_args[0]))
		return (0);
	for(int i=0; real_args[i]; i++)
	{
		printf("real_args[%s]\n", real_args[i]);
	}
	cmd_path = arg_cmds(real_args[0], env);
	if (cmd_path)
		real_args[0] = cmd_path;
	else
		return (write(2, "command not found\n", 19),
			ft_exit(127, SET_EXIT_STATUS), 127);
	return (execute_command_withargs(ast, env, real_args));
}
