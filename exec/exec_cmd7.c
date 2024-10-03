/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:56:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/03 11:20:03 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_size_arg(t_arg_node	*current)
{
	int			size;

	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	count_size_redir(t_redir_list	*current)
{
	int			size;

	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
char	**list_to_array(t_arg_node *lst, t_astnode *ast)
{
	int				size;
	t_arg_node		*current;
	int				i;
	char			**array;
	t_redir_list	*redirs;

	i = 0;
	current = lst;
	redirs = ast->t_cmd.redirections;
	size = count_size_arg(current) + count_size_redir(redirs);
	array = gcalloc(sizeof(char *) * (size + 1));
	current = lst;
	while (i < count_size_arg(current))
	{
		if (current)
		{
			array[i] = ft_strdup(current->arg);
			current = current->next;
		}
		else
			array[i] = NULL;
		i++;
	}
	if(redirs)
	{
		while (i < size && redirs)
		{
			if (redirs->redir)
				array[i] = ft_strdup(redirs->redir->file);
			redirs = redirs->next;
			i++;
		}
	}
	array[size] = NULL;
	return (array);
}

int	special_cases2( t_arg_node *lst)
{
	if (!ft_strcmp(lst->arg, "\"\""))
	{
		write(2, "filename argument required\n", 28);
		ft_exit(127, SET_EXIT_STATUS);
		return (1);
	}
	else if (!ft_strcmp(lst->arg, "\'\'"))
	{
		write(2, "Command not found 5\n", 19);
		ft_exit(127, SET_EXIT_STATUS);
		return (1);
	}
	return (0);
}

int	check_valid2(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str && (str[0] == '=' || str[0] == '+'))
		return (0);
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9' && i == 0)
			return (0);
		if (
			!(
				('0' <= str[i] && str[i] <= '9')
				|| ('a' <= str[i] && str[i] <= 'z')
				|| ('A' <= str[i] && str[i] <= 'Z')
				|| str[i] == '_' || str[i] == '=' || str[i] == '+'
			)
		)
			return (0);
		if (str[i] == '+' && str[i + 1] != '=')
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
		if(i == 0 && '0' <= str[i] && str[i] <= '9')
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