/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:56:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/12 00:16:01 by ibes-sed         ###   ########.fr       */
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
			*(array)[*i] = ft_strdup((*current)->arg);
			*current = (*current)->next;
		}
		else
			*(array)[*i] = NULL;
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
		write(2, "Command not found\n", 19);
		ft_exit(127, SET_EXIT_STATUS);
		return (1);
	}
	return (0);
}
