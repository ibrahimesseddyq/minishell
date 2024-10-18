/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:13:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/18 01:25:59 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_var;

void	execute(t_tklist *token_list, t_astnode *ast, t_lst *lst, char *t)
{
	token_list = tokenize(t);
	if (token_list->size > 1)
		add_history(t);
	if (!analyse_syntax(token_list) || !valid_quotes_main(t))
		ft_exit(258, SET_EXIT_STATUS);
	else
	{
		set_beginning(token_list);
		ast = parse_command_line(token_list, lst);
		if (ast)
			exec_cmd_line(ast, lst);
	}
}
void	handle_arguments_main(int ac, char **av)
{
	if (ac > 1)
	{
		printf("run ./minishell with no args\n");
		ft_exit(1, EXIT_PROGRAM);
	}
}
int	main(int ac, char **av, char *env[])
{
	t_tklist	*token_list;
	t_astnode	*ast;
	t_lst		*lst;
	char		*t;

	(void)((1) && (token_list = NULL, ast = NULL, initialize(), lst = envp(env), 1));
	handle_arguments_main(ac, av);
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
		printf("\nexit status: [%d]\n", ft_exit(1, GET_EXIT_STATUS));
		unlink_heredocs();
		free(t);
	}
	return (gc_free_all(), ft_exit(1, GET_EXIT_STATUS));
}
