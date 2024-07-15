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
	printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

int main(int ac, char **av, char *env[]) {
	(void)ac;
	(void)av;

	t_tklist *token_list;
	t_astnode *ast;
	t_st st;
	t_lst *lst;
	st.st = 0;
	st.status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_catch_signals = 0;




// the first main();


	while (1)
	{
		char *t = readline("minishell:>$ ");
		if (!t)
		{
			printf("exit\n");
			exit(0);
		}
		if(t)
			add_history(t);
		token_list = tokenize(t);
		if (!analyse_syntax(token_list))
		{
			exit(0);
		}
		set_beginning(token_list);

		ast = parse_command_line(token_list);	
		lst = envp(env);
		if (!lst)
			printf("nop\n");
		if (ft_strncmp(ast->t_cmd.args[0], "env", 3) == 0)
		{
			while (lst)
			{
				printf("%s=%s\n", lst->key, lst->value);
				lst = lst->next;
			}
		}
		if (ast)
		{
			// expand();
			// if (!strcmp(ast->t_cmd.args[0], "export"))
			// 	printf("export here \n");
			// else
				exec_cmd_line(ast, &st);
			// print_ast(ast, 0);
		}
	}
	return 0;
}
