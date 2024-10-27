/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:21:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/27 22:01:33 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	choose_splitting_delimiter(t_arg_node	*lst, t_astnode *ast)
{
	which_to_split_with(list_to_array(lst, ast), 1);
	which_to_split_with(list_to_array(lst, ast), 2);
	which_to_split_with(list_to_array(lst, ast), 3);
	which_to_split_with(list_to_array(lst, ast), 4);
	which_to_split_with(list_to_array(lst, ast), 5);
}

void	remove_ampersand_strings(char **arr, int *size)
{
	size_t	read_index;
	size_t	write_index;

	if (!arr)
		return ;
	read_index = 0;
	write_index = 0;
	while (arr[read_index] != NULL)
	{
		if (ft_strcmp(arr[read_index], get_null_str()) != 0)
		{
			if (ft_strcmp(arr[read_index], get_empty_str()) == 0)
				arr[write_index] = ft_strdup("");
			else
				arr[write_index] = make_empty_and_null(arr[(int)read_index]);
			write_index++;
		}
		read_index++;
	}
	arr[write_index] = NULL;
	*size = write_index;
}

int	is_builtin_command(const char *cmd)
{
	return (!ft_strcmp((char *)cmd, "echo") || !ft_strcmp((char *)cmd, "cd")
		|| !ft_strcmp((char *)cmd, "pwd") || !ft_strcmp((char *)cmd, "env")
		|| !ft_strcmp((char *)cmd, "exit") || !ft_strcmp((char *)cmd, "export")
		|| !ft_strcmp((char *)cmd, "unset"));
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

int	initial_builtin_errors(t_arg_node *args)
{
	char		*cmd;
	t_arg_node	*arg;

	if (!args || !args->arg)
		return (0);
	cmd = args->arg;
	if ((!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")))
	{
		arg = args->next;
		while (arg)
		{
			arg = arg->next;
		}
	}
	return (0);
}
