/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/06 12:39:45 by armanov          ###   ########.fr       */
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


void	ft_red_out(t_astnode *ast)
{
	int fd;
	
	fd = 0;
	// printf("\n\n\nhiiiii this is size : %d\n\n\n\n\n\n", count_red(ast));
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
	close (fd);
}
