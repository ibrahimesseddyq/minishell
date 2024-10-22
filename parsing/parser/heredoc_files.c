/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:59:46 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 00:10:13 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	add_heredoc_to_list(char *heredoc_file)
{
	t_list	**lst;
	char	*heredoc_content;
	t_list	*heredoc;

	lst = get_heredoc_list();
	heredoc_content = ft_strdup(heredoc_file);
	if (heredoc_content == NULL)
		return ;
	heredoc = ft_lstnew(heredoc_content);
	if (heredoc == NULL)
		return ;
	ft_lstadd_back(lst, heredoc);
}

t_list	**get_heredoc_list(void)
{
	static t_list	*lst;

	return (&lst);
}

void	unlink_heredocs(void)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *get_heredoc_list();
	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		unlink(tmp->content);
		tmp = tmp->next;
	}
	*get_heredoc_list() = NULL;
}
