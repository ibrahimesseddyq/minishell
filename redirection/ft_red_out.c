/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/24 18:20:47 by ynachat          ###   ########.fr       */
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
	while (start->t_cmd.outfile != NULL)
	{
		start->t_cmd.outfile = start->t_cmd.outfile->next;
		i++;
	}
	return (i);
}


void	ft_red_out(t_astnode *ast)
{
	int fd;
	
	fd = 0;
	printf("\n\n\nhiiiii this is size : %d\n\n\n\n\n\n", count_red(ast));
	if (ast->t_cmd.outfile && ast->t_cmd.outfile->redir && ast->t_cmd.outfile->redir->type == NODE_REDIRECT_OUT)
	{
		fd = open(ast->t_cmd.outfile->redir->file , O_WRONLY | O_CREAT  | O_TRUNC, 0777);
		if (fd < 0)
		{
			printf("fd outfile 1 fail!!\n");
			close (fd);
			exit(1);
		}
		printf("her is node red\n");
		dup2(fd, 1);
	}else if (ast->t_cmd.append && ast->t_cmd.append->redir && ast->t_cmd.append->redir->type == NODE_REDIRECT_APPEND)
	{
		fd = open(ast->t_cmd.append->redir->file, O_WRONLY | O_CREAT  | O_APPEND, 0777);
		if (fd < 0)
		{
			printf("fd outfile 2 fail!!\n");
			close (fd);
			exit(1);
		}
		printf("her is node append\n");
		dup2(fd, 1);
	}
}
