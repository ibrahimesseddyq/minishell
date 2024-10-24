/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:17:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 22:38:06 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_var = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_exit(1, SET_EXIT_STATUS);
	}
}

void	increment_shell_level(t_lst *env)
{
	int	shlvl;
	char	*shlvlstr;

	shlvlstr = get_env(env, "SHLVL");
	if (shlvlstr && shlvlstr[0])
	{
		shlvl = ft_atoi(shlvlstr);
		shlvl++;
		set_env(env, "SHLVL", ft_itoa(shlvl), 1);
	}
}

void	initialize(t_tklist **token_list, t_astnode	**ast)
{
	ast = NULL;
	token_list = NULL;
	signal(SIGQUIT, handle_sig);
	signal(SIGINT, handle_sig);
	g_sig_var = 0;
	rl_catch_signals = 0;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		write(2, "non interactive mode is unavailable\n", 37);
		gc_free_all();
		ft_exit(1, EXIT_PROGRAM);
	}
}

int	valid_quotes_main(char *line)
{
	int	quotes_valid;

	quotes_valid = is_valid_quotes(line);
	if (!quotes_valid)
		return (write(2, "syntax error in quotes\n", 24), 0);
	return (1);
}
