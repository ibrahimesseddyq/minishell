#include "minishell.h"
#include "./frontend/frontend.h"
#include <signal.h>

void f()
{
	// system("leaks ./minishell");
}

void handle_sigint(int num)
{
	(void)num;
    rl_replace_line("", 0);
    // rl_on_new_line();
    rl_redisplay();
}
// void increment_shell_level(t_lst* env)
// {
// 	int shlvl;

// 	shlvl = ft_atoi(get_env(env, "SHLVL"));
// 	shlvl++;
// 	set_env(env, "SHLVL", itoa(shlvl), 1);
// }
// change std function with my libft atoi, printf...
int main(int ac, char **av, char *env[])
{
	(void)ac;
	(void)av;
	(void)env;

	setbuf(stdout, NULL);
	t_tklist *token_list;
	t_astnode *ast;
	t_lst *lst;
	t_lst *tmp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_catch_signals = 0;

	lst = envp(env);

	tmp = lst;
	while (1)
	{
		char *t = readline("minishell:>$ ");
		if (!t)
		{
			printf("exit 2\n");
			exit(2); 
		}
		if(t)
		{

			token_list = tokenize(t);
			if (!analyse_syntax(token_list))
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
			}
		}
	}
	return (ft_exit(1, GET_EXIT_STATUS));
}
