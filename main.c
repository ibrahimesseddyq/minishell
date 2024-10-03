/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:13:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/03 12:33:49 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
int sig_var;

// void	signal_ctlc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDERR_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }


void f()
{
	system("leaks minishell");
}
void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		sig_var = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{

	}
}

void	increment_shell_level(t_lst *env)
{
	int	shlvl;

	shlvl = ft_atoi(get_env(env, "SHLVL"));
	shlvl++;
	set_env(env, "SHLVL", ft_itoa(shlvl), 1);
}

void	initialize()
{
	signal(SIGQUIT, handle_sig);
	signal(SIGINT, handle_sig);
	sig_var = 0;
	rl_catch_signals = 0;
	if (!isatty(0))
	{
		write(2, "non interactive mode is unavailable\n", 37);
		ft_exit(1, EXIT_PROGRAM);
	}
}
int valid_quotes_main(char *line)
{
	int	quotes_valid;

	quotes_valid = is_valid_quotes(line);
	if (!quotes_valid)
		return (write(2, "syntax error in quotes\n", 24), 0);
	return (1);
}

int	main(int ac, char **av, char *env[])
{
	t_tklist	*token_list;
	t_astnode	*ast;
	t_lst		*lst;
	t_lst		*tmp;
	char		*t;

	(void)ac;
	(void)av;
	(void)env;
	// signal(SIGQUIT, SIG_IGN);
	initialize();
	// atexit(f);
	lst = envp(env);
	increment_shell_level(lst);
	tmp = lst;
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
		{
			token_list = tokenize(t);
			if (!analyse_syntax(token_list) || !valid_quotes_main(t))
			{
				ft_exit(258, SET_EXIT_STATUS);
			}
			else
			{
				add_history(t);
				set_beginning(token_list);
				ast = parse_command_line(token_list, lst);
				lst = tmp;
				if (ast)
					exec_cmd_line(ast, lst);
				printf("exit status >>>>>. %d\n", ft_exit(2, GET_EXIT_STATUS));
			}
		}
		sig_var = 0;
		unlink_heredocs();
	}
	gc_free_all();
	return (ft_exit(1, GET_EXIT_STATUS));
}
