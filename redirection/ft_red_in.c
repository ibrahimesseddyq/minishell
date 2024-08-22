/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:22:35 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/22 18:08:44 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int	ft_red_in(t_astnode *ast)
{
	int fd;

	fd = 0;
	if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir && ast->t_cmd.redirections->redir->type == NODE_REDIRECT_IN)
	{

		fd = open(ast->t_cmd.redirections->redir->file , O_RDONLY, 0644);
		if (fd < 0)
		{
			printf("fd infile 1 fail!!\n");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	// else
	// {
	// 	//herdoc
	// 	// fd = open(ast.t_cmd.infile->file, O_RDONLY | O_CREAT , 0644);
	// 	// if (fd < 0)
	// 	// {
	// 	// 	printf("fd infile 2 fail!!\n");
	// 	// close (fd);
	// 	// 	exit(1);
	// 	// }
	// 	// dup2(fd, 0);
	// }
	return (fd);
}
