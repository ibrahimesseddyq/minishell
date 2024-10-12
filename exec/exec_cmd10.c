/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:28:02 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/11 22:28:13 by ibes-sed         ###   ########.fr       */
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
