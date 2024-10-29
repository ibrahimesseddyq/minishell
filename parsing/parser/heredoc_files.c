/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:59:46 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 08:13:37 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	add_heredoc_fd_to_list(int *fd)
{
	t_list	**lst;
	int		*heredoc_content;
	t_list	*heredoc;

	lst = get_heredoc_list();
	heredoc_content = fd;
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

void	close_heredocs(void)
{
	t_list	*lst;
	t_list	*tmp;
	int		*fd;

	lst = *get_heredoc_list();
	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		fd = tmp->content;
		ft_close(fd);
		tmp = tmp->next;
	}
	*get_heredoc_list() = NULL;
}
