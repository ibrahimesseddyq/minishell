/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:22:07 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/16 17:08:06 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

static int check_and_open_file(const char *file, int flags, mode_t mode)
{ 
    struct stat sb;

    if (stat(file, &sb) == -1) {
        int fd = open(file, flags, mode);
        if (fd == -1)
        {
            if(access(file, F_OK) == 0 && access(file, W_OK) == -1)
				fprintf(stderr,"Permission denied\n");
			else
				fprintf(stderr,"No such file or directory\n");
        	ft_exit(1, SET_EXIT_STATUS);
			return (-2);

        }
        return fd;  // File successfully opened/created
    }

    // If the file exists and is not a regular file, return an error
    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr,"Error: Path is not a regular file\n");
        ft_exit(1, SET_EXIT_STATUS);
				return (-2);
    }

    // Open the file normally if it exists
    int fd = open(file, flags, mode);
    if (fd == -1) {
        perror("Error opening file");
        ft_exit(1, SET_EXIT_STATUS);
		return (-2);
    }

    return fd;
}

int ft_red_out(t_astnode *ast, t_lst *env, int is_last, int command_exist)
{
					int devnull;
    int fd = 0;
    if (ast->t_cmd.redirections && ast->t_cmd.redirections->redir)
    {
        t_redir *redir = ast->t_cmd.redirections->redir;
        ast->t_cmd.redirections->redir->file = ft_expand_redir(ast->t_cmd.redirections->redir->file, env);

        if (!ast->t_cmd.redirections->redir->file)
        {
            fprintf(stderr,"ambigiuos redir\n");
            return (-2);
        }
        if (redir->type == NODE_REDIRECT_OUT)
        {
            fd = check_and_open_file(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            if (fd == -2)
				return (-2);
            if (is_last && command_exist)
			    dup2(fd, 1);
            if (!command_exist && fd)
                ft_exit(0, SET_EXIT_STATUS);
        } else if (redir->type == NODE_REDIRECT_APPEND)
        {
            fd = check_and_open_file(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fd == -2)
				return (-2);
            if (is_last && command_exist)
			    dup2(fd, 1);
            if (!command_exist && fd)
                ft_exit(0, SET_EXIT_STATUS);
        }
    }
    
    return fd;
}
