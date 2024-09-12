/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:22:35 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/12 18:51:12 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"
#include <fcntl.h>   // For open()
#include <unistd.h>  // For write(), dup2(), close()
#include <sys/stat.h> // For stat()
#include <stdio.h>   // For perror(), printf()
#include <stdlib.h>  // For exit()

static int check_and_open_file(const char *file, int flags, mode_t mode)
{
    struct stat sb;

    if (stat(file, &sb) == -1)
	{
        int fd = open(file, flags, mode);
        if (fd == -1)
		{
			if(access(file, F_OK) == 0 && access(file, R_OK) == -1)
				fprintf(stderr,"Permission denied\n");
			else
				fprintf(stderr,"No such file or directory\n");
        	ft_exit(1, SET_EXIT_STATUS);
			return (-2);
        }
        return fd;
    }

    if (!S_ISREG(sb.st_mode))
	{
        fprintf(stderr,"Error: Path is not a regular file\n");
        ft_exit(1, SET_EXIT_STATUS);
		return (-2);
    }
    int fd = open(file, flags, mode);
    if (fd == -1) {
        perror("Error opening file");
        ft_exit(1, SET_EXIT_STATUS);
		return (-2);
    }

    return fd;
}
int	ft_red_in(t_astnode *ast, t_lst *env, int is_last)
{
	int fd;

	fd = 0;
        ast->t_cmd.redirections->redir->file = ft_expand_redir(ast->t_cmd.redirections->redir->file, env);
        if (!ast->t_cmd.redirections->redir->file)
        {
            fprintf(stderr,"ambigiuos redir\n");
            return (-2);
        }
	if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir && ast->t_cmd.redirections->redir->type == NODE_REDIRECT_IN)
	{

		fd = check_and_open_file(ast->t_cmd.redirections->redir->file , O_RDONLY, 0644);
		if (fd == -2)
			return (-2);
		if (fd < 0)
		{
			close(fd);
			exit(1);
		}
		if (is_last)
			dup2(fd, 0);
	}
	else
	{
		fd = check_and_open_file(ast->t_cmd.redirections->redir->heredoc , O_RDONLY | O_CREAT , 0644);
		if (fd == -2)
			return (-2);
		if (fd < 0)
		{
			close (fd);
			exit(1);
		}
		if (is_last)
			dup2(fd, 0);

	}
	return (fd);
}
