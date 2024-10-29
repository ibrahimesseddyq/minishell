/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:13:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 09:00:30 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_var;

void	close_all_heredoc_fds(t_astnode *ast)
{
	t_redir_list	*redirects;

	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
	{
		redirects = ast->t_cmd.redirections;
		while (redirects)
		{
			if (redirects->redir && redirects->redir->type == NODE_HEREDOC
				&& redirects->redir->fd_heredoc_rd
				&& *(redirects->redir->fd_heredoc_rd) != -1)
				(1) && (ft_close(redirects->redir->fd_heredoc_rd),
					*(redirects->redir->fd_heredoc_rd) = -1);
			redirects = redirects->next;
		}
	}
	else if (ast->type == NODE_PIPE || ast->type == NODE_LOGICAL_AND
		|| ast->type == NODE_LOGICAL_OR || ast->type == NODE_SEQUENCE)
	{
		close_all_heredoc_fds(ast->t_binary.left);
		close_all_heredoc_fds(ast->t_binary.right);
	}
	else if (ast->type == NODE_SUBSHELL || ast->type == NODE_BLOCK)
		close_all_heredoc_fds(ast->t_block.child);
}

void	execute_main(t_tklist *token_list, t_astnode *ast, t_lst *lst, char *t)
{
	token_list = tokenize(t);
	if (t && ft_strlen(t) > 0)
		add_history(t);
	if (!analyse_syntax(token_list) || !valid_quotes_main(t))
		ft_exit(258, SET_EXIT_STATUS);
	else
	{
		set_beginning(token_list);
		ast = parse_command_line(token_list, lst);
		if (ast)
		{
			exec_cmd_line(ast, lst);
		}
		close_all_heredoc_fds(ast);
	}
}

void	handle_arguments_main(int ac, char **av)
{
	(void)av;
	if (ac > 1)
	{
		printf("run ./minishell with no args\n");
		gc_free_all();
		ft_exit(1, EXIT_PROGRAM);
	}
}

int	main(int ac, char **av, char *env[])
{
	t_tklist	*token_list;
	t_astnode	*ast;
	t_lst		*lst;
	char		*t;

	(void)((1) && (initialize(&token_list, &ast), lst = envp(env), 1));
	handle_arguments_main(ac, av);
	while (1)
	{
		t = readline("minishell:>$ ");
		if (!t)
		{
			printf("exit\n");
			gc_free_all();
			exit(ft_exit(1, GET_EXIT_STATUS));
		}
		if (t)
			execute_main(token_list, ast, lst, t);
		printf("exit status [%d]\n", ft_exit(1, GET_EXIT_STATUS));
		close_heredocs();
		g_sig_var = 0;
		free(t);
	}
	return (gc_free_all(), ft_exit(1, GET_EXIT_STATUS));
}
