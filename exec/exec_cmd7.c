/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:56:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/27 22:02:06 by ibes-sed         ###   ########.fr       */
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

void	replace_args(int *i, t_arg_node **current, char ***array)
{
	while (*i < count_size_arg(*current))
	{
		if (*current)
		{
			(*array)[*i] = ft_strdup((*current)->arg);
			*current = (*current)->next;
		}
		else
			(*array)[*i] = NULL;
		(*i)++;
	}
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
	replace_args(&i, &current, &array);
	if (redirs)
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

int	is_directory(char *cmd)
{
	struct stat	info;

	stat(cmd, &info);
	if (S_ISDIR(info.st_mode))
	{
		return (0);
	}
	else if (S_ISREG(info.st_mode))
	{
		return (2);
	}
	return (1);
}
