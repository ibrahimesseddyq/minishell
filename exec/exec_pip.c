/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:51 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/08 10:37:43 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_pip(t_astnode *ast, t_lst *env)
{
    int pipfd[2];
    int prev_pipe_read = -1;
    pid_t last_pid = -1;

    while (ast->type == NODE_PIPE) {
        pipe(pipfd);

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            if (prev_pipe_read != -1) {
                dup2(prev_pipe_read, STDIN_FILENO);
                close(prev_pipe_read);
            }
            dup2(pipfd[1], STDOUT_FILENO);
            close(pipfd[0]);
            close(pipfd[1]);

            exec_cmd_line(ast->binary.left, env);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }

        // Parent process
        if (prev_pipe_read != -1)
            close(prev_pipe_read);
        close(pipfd[1]);
        prev_pipe_read = pipfd[0];

        ast = ast->binary.right;
    }

    // Last command in the pipeline
    last_pid = fork();
    if (last_pid == 0) {
        // Child process for last command
        if (prev_pipe_read != -1) {
            dup2(prev_pipe_read, STDIN_FILENO);
            close(prev_pipe_read);
        }
        exec_cmd_line(ast, env);
        exit(0);
    } else if (last_pid < 0) {
        perror("fork");
        exit(1);
    }

    // Parent process
    if (prev_pipe_read != -1)
        close(prev_pipe_read);

    // Wait only for the last process
    waitpid(last_pid, NULL, 0);
}

