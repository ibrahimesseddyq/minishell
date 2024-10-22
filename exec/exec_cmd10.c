/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:28:02 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 23:53:35 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_command_in_path(const char *cmd, char **path_dirs)
{
	char	*cmd_with_slash;
	int		i;
	char	*full_path;

	i = 0;
	cmd_with_slash = ft_strjoin("/", (char *)cmd);
	if (!cmd_with_slash)
		return (NULL);
	while (path_dirs[i])
	{
		full_path = ft_strjoin(path_dirs[i], cmd_with_slash);
		if (!full_path)
			continue ;
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
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

void	handle_expanding_of_argument(t_state_fs	*state, t_lst *env, char *cmd)
{
	state->expanded_arg = get_expanded_string(env, state->lst, cmd);
	if (star_not_inside_quotes(state->expanded_arg))
		state->star_inside = 1;
	if (state->star_inside)
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
		handle_expanding_of_argument(&state, env, ast->t_cmd.args[0].arg);
	}
	state.lst = state.head;
	state.splitted_args
		= ft_split_quotes(state.expanded_string, *get_splitted_char(1));
	if (!state.splitted_args)
		return (0);
	ast->t_cmd.args_size = state.i;
	return (split_all_strings(state.splitted_args, *get_splitted_char(2)));
}

int	star_not_inside_quotes(const char *str)
{
	int	inside_quotes;

	inside_quotes = 0;
	while (*str)
	{
		if (*str == '"')
			inside_quotes = !inside_quotes;
		if (*str == *get_splitted_char(4) && !inside_quotes)
			return (1);
		str++;
	}
	return (0);
}
