/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/19 04:07:40 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void	ft_red_out(t_astnode *ast)
{
	int fd;
	
	fd = 0;
	if (ast->t_cmd.outfile && ast->t_cmd.infile->type == NODE_REDIRECT_OUT)
	{
		fd = open(ast->t_cmd.outfile->file, O_WRONLY | O_CREAT  | O_TRUNC, 0777);
		if (fd < 0)
		{
			printf("fd outfile 1 fail!!\n");
			close (fd);
			exit(1);
		}
		printf("her is node red\n");
		dup2(fd, 1);
		close (fd);

	}else if (ast->t_cmd.outfile && ast->t_cmd.outfile->type == NODE_REDIRECT_APPEND)
	{
		fd = open(ast->t_cmd.outfile->file, O_WRONLY | O_CREAT  | O_APPEND, 0777);
		if (fd < 0)
		{
			printf("fd outfile 2 fail!!\n");
			close (fd);
			exit(1);
		}
		printf("her is node append\n");
		dup2(fd, 1);
		close (fd);
	}
}