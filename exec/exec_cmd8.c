/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:46:03 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/08 14:56:55 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_valid_key_export(char c)
{
	return (!(
				('0' <= c && c <= '9')
				|| ('a' <= c && c <= 'z')
				|| ('A' <= c && c <= 'Z') || c == '*'
				|| c == '_' || c == '=' || c == '+' || c== '\"' || c == '\'' || c == '$'
			));
}
int	check_valid2(char *str)
{
	int	i;
	int equal;

	if (!str || !str[0])
		return (0);
	i = 0;
	equal = 0;
	if (str && (str[0] == '=' || str[0] == '+'))
		return (0);
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9' && i == 0)
			return (0);
		if (is_valid_key_export(str[i]))
			return (0);
		if (str[i] == '=')
			equal = 1;
		if (str[i] == '+' && str[i + 1] != '=')
			return (0);
		if (str[i] == '*' && equal == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_valid1(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (i == 0 && '0' <= str[i] && str[i] <= '9')
			return (0);
		if (
			!(
				('0' <= str[i] && str[i] <= '9')
				|| ('a' <= str[i] && str[i] <= 'z')
				|| ('A' <= str[i] && str[i] <= 'Z')
				|| str[i] == '_'
			)
		)
			return (0);
		i++;
	}
	return (1);
}

int	command_is_empty(char *str)
{
	if (!ft_strcmp("\"\"", str) || !ft_strcmp("\'\'", str))
		return (1);
	return (0);
}

int	no_command_case(t_arg_node *lst, t_lst *env, t_astnode *ast)
{
	int	stdout_backup;

	stdout_backup = -1;
	if (!lst || (lst && command_is_empty(lst->arg)))
	{
		stdout_backup = ft_redirection(ast, env, 0);
		if (stdout_backup == -2)
			return (-2);
		ft_close(&stdout_backup);
		if (lst && command_is_empty(lst->arg))
		{
			write(2, "Command not found\n", 19);
			ft_exit(127, SET_EXIT_STATUS);
			return (1);
		}
	}
	return (0);
}
