/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:13:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 15:18:23 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_var;

void	execute(t_tklist *token_list, t_astnode *ast, t_lst *lst, char *t)
{
	token_list = tokenize(t);
	if (!analyse_syntax(token_list) || !valid_quotes_main(t))
		ft_exit(258, SET_EXIT_STATUS);
	else
	{
		set_beginning(token_list);
		ast = parse_command_line(token_list, lst);
		if (ast)
			exec_cmd_line(ast, lst);
	}
	add_history(t);
}

int	main(int ac, char **av, char *env[])
{
	t_tklist	*token_list;
	t_astnode	*ast;
	t_lst		*lst;
	char		*t;

	(1) && ((void)ac, (void)av, 1);
	initialize();
	lst = envp(env);
	increment_shell_level(lst);
	while (1)
	{
		t = readline("minishell:>$ ");
		if (!t)
		{
			printf("exit 2\n");
			gc_free_all();
			exit(2);
		}
		if (t)
			execute(token_list, ast, lst, t);
		g_sig_var = 0;
		unlink_heredocs();
	}
	gc_free_all();
	return (ft_exit(1, GET_EXIT_STATUS));
}
