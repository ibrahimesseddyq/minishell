/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:56:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 21:57:43 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_size(t_arg_node	*current)
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

char	**list_to_array(t_arg_node *lst)
{
	int			size;
	t_arg_node	*current;
	int			i;
	char		**array;

	i = 0;
	current = lst;
	size = count_size(current);
	array = gcalloc(sizeof(char *) * (size + 1));
	current = lst;
	while (i < size)
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
