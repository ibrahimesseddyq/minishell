/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:51 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/09 15:33:38 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"

// void exec_pip(t_astnode *ast, t_lst *env)
// {
//     int pipfd[2];
//     int prev_pipe_read = -1;
//     pid_t last_pid = -1;

//     while (ast->type == NODE_PIPE) {
//         pipe(pipfd);

//         pid_t pid = fork();
//         if (pid == 0) {
//             // Child process
//             if (prev_pipe_read != -1) {
//                 dup2(prev_pipe_read, STDIN_FILENO);
//                 close(prev_pipe_read);
//             }
//             dup2(pipfd[1], STDOUT_FILENO);
//             close(pipfd[0]);
//             close(pipfd[1]);

//             exec_cmd_line(ast->binary.left, env);
//             exit(0);
//         } else if (pid < 0) {
//             perror("fork");
//             exit(1);
//         }

//         // Parent process
//         if (prev_pipe_read != -1)
//             close(prev_pipe_read);
//         close(pipfd[1]);
//         prev_pipe_read = pipfd[0];

//         ast = ast->binary.right;
//     }

//     // Last command in the pipeline
//     last_pid = fork();
//     if (last_pid == 0) {
//         // Child process for last command
//         if (prev_pipe_read != -1) {
//             dup2(prev_pipe_read, STDIN_FILENO);
//             close(prev_pipe_read);
//         }
//         exec_cmd_line(ast, env);
//         exit(0);
//     } else if (last_pid < 0) {
//         perror("fork");
//         exit(1);
//     }

//     // Parent process
//     if (prev_pipe_read != -1)
//         close(prev_pipe_read);

//     // Wait only for the last process
//     waitpid(last_pid, NULL, 0);
// }

void exec_pip(t_astnode *ast, t_lst *env)
{
	// int		i;
	// int		j;
	int		pipfd[2];
	int		pid;
	int		pid2;
	// char	**cmd1;
	// char	**cmd2;
	// i = 0;
	// j = 0;
	// exit(1);
	// cmd1 = ast->binary.left->t_cmd.args;
	// cmd2 = ast->binary.right->t_cmd.args;
	// char *arg_cmd1[] = {arg_cmds(cmd1[0]), cmd1[1], NULL};
	// char *arg_cmd2[] = {arg_cmds(cmd2[0]), cmd2[1], NULL};

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipfd[1], 1);
		close(pipfd[0]);
		exec_cmd_line(ast->binary.left, env);
		exit(0);
		// if (execve(arg_cmds(cmd1[0]), arg_cmd1, NULL) == -1)
		// {
		// 	write(2, "Error\nexecve1()!!!\n", 19);
		// 	exit(1);
		// }
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipfd[0], 0);
		close(pipfd[1]);
		exec_cmd_line(ast->binary.right, env);
		exit(0);
		// if (execve(arg_cmds(cmd2[0]), arg_cmd2, NULL) == -1)
		// {
		// 	write(2, "Error\nexecve2()!!!\n", 19);
		// 	exit(1);
		// }
	}
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
}
