/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/21 03:39:29 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void	ft_red_out(t_astnode *ast)
{
	int fd;
	
	fd = 0;

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
