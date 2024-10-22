/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:21:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 05:46:32 by ibes-sed         ###   ########.fr       */
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
	printf("nullstr[%s] emptystr[%s]\n", get_null_str(), get_empty_str());
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

char	**handle_empty_var_beginning(char **real_args)
{
	int	i;

	i = 0;
	while (real_args && real_args[i]
		&& (!real_args[i][0] || real_args[i][0] == '\0'))
		i++;
	if (real_args[i])
		return (real_args + i);
	else
		return (NULL);
}

int	is_builtin_command(const char *cmd)
{
	return (!ft_strcmp((char *)cmd, "echo") || !ft_strcmp((char *)cmd, "cd")
		|| !ft_strcmp((char *)cmd, "pwd") || !ft_strcmp((char *)cmd, "env")
		|| !ft_strcmp((char *)cmd, "exit") || !ft_strcmp((char *)cmd, "export")
		|| !ft_strcmp((char *)cmd, "unset"));
}

void	setup_env_and_exec(char **arg_cmd, t_lst *env, int fd)
{
	char	**envp;

	envp = build_envp(env);
	if (!envp)
		exit(1);
	if (!check_file(arg_cmd))
	{
		ft_close(&fd);
		exit(127);
	}
	if (execve(arg_cmd[0], arg_cmd, envp) == -1)
	{
		handle_exec_error();
		exit(1);
	}
}
