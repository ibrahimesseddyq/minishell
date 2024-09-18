/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:20 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 21:58:18 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_array(char **args, int size)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (i <= size && args[i])
	{
		str = args[i];
		printf("argv[i] inside [%s]\n", args[i]);
		j = 0;
		while (str[j])
		{
			if (str[j] == *get_splitted_char(2))
				str[j] = ' ';
			j++;
		}
		i++;
	}
	return (args);
}

int	builtins_error(char **argv)
{
	int	i;
	int	command;

	i = 0;
	command = 0;
	printf("argv is [%s]\n", argv[0]);
	if (!argv[0])
	{
		write(2, "command not found\n", 19);
		ft_exit(127, SET_EXIT_STATUS);
		return (1);
	}
	if (!ft_strcmp(argv[0], "export"))
		command = IS_EXPORT;
	while (argv[i])
	{
		if (command == IS_EXPORT && check_export_errors(argv[i]))
			return (ft_exit(1, SET_EXIT_STATUS),
				write(2, "not a valid identifier\n", 24), 1);
		i++;
	}
	return (0);
}

int	special_cases( t_arg_node *lst)
{
	if (!ft_strcmp(lst->arg, "."))
	{
		write(2, "filename argument required\n", 28);
		ft_exit(2, SET_EXIT_STATUS);
		return (1);
	}
	else if (!ft_strcmp(lst->arg, ".."))
	{
		write(2, "Command not found\n", 19);
		ft_exit(127, SET_EXIT_STATUS);
		return (1);
	}
	else if (lst->arg[ft_strlen(lst->arg) - 1] == '/')
	{
		write(2, "Is a directory\n", 16);
		ft_exit(126, SET_EXIT_STATUS);
		return (1);
	}
	return (0);
}

int	no_command_case(t_arg_node *lst, t_lst *env, t_astnode *ast)
{
	int	stdout_backup;

	if (!lst)
	{
		stdout_backup = ft_redirection(ast, env, 0);
		if (stdout_backup == -2)
			return (-2);
		close(stdout_backup);
	}
	return (0);
}
