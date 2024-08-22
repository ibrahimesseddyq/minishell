/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/22 18:09:36 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int	count_red(t_astnode *lst)
{
	t_astnode	*start;
	int		i;

	if (lst == NULL)
		return (0);
	start = lst;
	i = 0;
	while (start->t_cmd.redirections != NULL)
	{
		start->t_cmd.redirections = start->t_cmd.redirections->next;
		i++;
	}
	return (i);
}


int	ft_red_out(t_astnode *ast)
{
	int fd;
	
	fd = 0;
	if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir && ast->t_cmd.redirections->redir->type == NODE_REDIRECT_OUT)
	{
		fd = open(ast->t_cmd.redirections->redir->file , O_WRONLY | O_CREAT  | O_TRUNC, 0777);
		if (fd < 0)
		{
			printf("fd outfile 1 fail!!\n");
			exit(1);
		}
		dup2(fd, 1);
	}else if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir && ast->t_cmd.redirections->redir->type == NODE_REDIRECT_APPEND)
	{
		fd = open(ast->t_cmd.redirections->redir->file, O_WRONLY | O_CREAT  | O_APPEND, 0777);
		if (fd < 0)
		{
			printf("fd outfile 2 fail!!\n");
			exit(1);
		}
		dup2(fd, 1);
	}
	return (fd);
}
